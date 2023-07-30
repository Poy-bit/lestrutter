#include "ol_mesh.h"

ol_mesh::ol_mesh(tinygltf::Model model, int node_index) {
	tinygltf::Node node = model.nodes[node_index];
	tinygltf::Mesh mesh = model.meshes[node.mesh];

	tinygltf::Primitive material_primitive = mesh.primitives[0];
	tinygltf::Primitive outline_primitive = mesh.primitives[1];

	tinygltf::Accessor pos_accessor = model.accessors[material_primitive.attributes["POSITION"]];
	tinygltf::Accessor opos_accessor = model.accessors[outline_primitive.attributes["POSITION"]];
	tinygltf::BufferView pos_bufferview = model.bufferViews[pos_accessor.bufferView];
	tinygltf::BufferView opos_bufferview = model.bufferViews[opos_accessor.bufferView];

	// Sanity Check
	assert(pos_accessor.componentType == GL_FLOAT);
	assert(pos_accessor.count == pos_bufferview.byteLength / sizeof(float) / pos_accessor.type);

	mvc = pos_accessor.count;
	indices_count = model.accessors[material_primitive.indices].count + model.accessors[outline_primitive.indices].count;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	std::vector<char> data(pos_bufferview.byteLength + opos_bufferview.byteLength, 0);
	data.insert(data.begin(),
		&model.buffers[pos_bufferview.buffer].data[0] + pos_bufferview.byteOffset,
		&model.buffers[pos_bufferview.buffer].data[0] + pos_bufferview.byteOffset + pos_bufferview.byteLength);
	data.insert(data.begin() + pos_bufferview.byteLength,
		&model.buffers[opos_bufferview.buffer].data[0] + opos_bufferview.byteOffset,
		&model.buffers[opos_bufferview.buffer].data[0] + opos_bufferview.byteOffset + opos_bufferview.byteLength);

	glBufferData(pos_bufferview.target, pos_bufferview.byteLength + opos_bufferview.byteLength, &data[0], GL_STATIC_DRAW);
	lbuf_indices(model, material_primitive.indices, outline_primitive.indices, pos_accessor.count);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Remember to change stride when you add attribs to this buffer
	glVertexAttribPointer(0, pos_accessor.type, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
}

void ol_mesh::draw() {
	glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_SHORT, 0);
}

void ol_mesh::lbuf_indices(tinygltf::Model model, int mat_prim, int out_prim, int vert_count) {
	tinygltf::Accessor idx_accessor = model.accessors[mat_prim];
	tinygltf::Accessor oidx_accessor = model.accessors[out_prim];
	tinygltf::BufferView idx_bufferview = model.bufferViews[idx_accessor.bufferView];
	tinygltf::BufferView oidx_bufferview = model.bufferViews[oidx_accessor.bufferView];

	// sanity check
	assert(idx_accessor.componentType == GL_UNSIGNED_SHORT);
	assert(idx_accessor.count == idx_bufferview.byteLength / sizeof(short));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	std::vector<short> index_data;
	short* buffer_vector = (short*)model.buffers[idx_bufferview.buffer].data.data() + idx_bufferview.byteOffset / sizeof(short);
	index_data.assign(buffer_vector, buffer_vector + idx_bufferview.byteLength / sizeof(short));
	buffer_vector = (short*)model.buffers[oidx_bufferview.buffer].data.data() + oidx_bufferview.byteOffset / sizeof(short);
	index_data.insert(index_data.begin() + index_data.size(),
		buffer_vector, buffer_vector + oidx_bufferview.byteLength / sizeof(short));

	for (int i = idx_accessor.count; i < idx_accessor.count + oidx_accessor.count; i++)
		index_data[i] = index_data[i] + vert_count;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx_bufferview.byteLength + oidx_bufferview.byteLength, &index_data[0], GL_STATIC_DRAW);
}