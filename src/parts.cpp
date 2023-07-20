#include "parts.h"

parts::parts() {
	// Load parts model from file
	std::string filename = SOURCE_PATH + std::string("/res/parts.glb");
	tinygltf::Model model;
	tinygltf::TinyGLTF loader;
	std::string err;
	std::string warn;

	bool res = loader.LoadBinaryFromFile(&model, &err, &warn, filename);
	if (!warn.empty()) {
		std::cout << "Loader Warning: " << warn << std::endl;
	}

	if (!err.empty()) {
		std::cout << "Loader Error: " << err << std::endl;
	}

	if (!res)
		std::cout << "Failed to load glTF: " << filename << std::endl;

	tinygltf::Scene scene = model.scenes[model.defaultScene];
	tinygltf::Node armature = model.nodes[scene.nodes[0]];
	tinygltf::Node node = model.nodes[armature.children[0]];
	tinygltf::Mesh mesh = model.meshes[node.mesh];

	tinygltf::Accessor pos_accessor = model.accessors[mesh.primitives[0].attributes["POSITION"]];
	tinygltf::BufferView pos_bufferview = model.bufferViews[pos_accessor.bufferView];
	tinygltf::Accessor index_accessor = model.accessors[mesh.primitives[0].indices];
	tinygltf::BufferView index_bufferview = model.bufferViews[index_accessor.bufferView];

	// Sanity Check
	assert(pos_accessor.componentType == GL_FLOAT);
	assert(pos_accessor.count == pos_bufferview.byteLength / sizeof(float) / pos_accessor.type);
	assert(index_accessor.componentType == GL_UNSIGNED_SHORT);
	assert(index_accessor.count == index_bufferview.byteLength / sizeof(short));

	indices_count = index_accessor.count;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	void* data = (void*)&model.buffers[pos_bufferview.buffer].data[pos_bufferview.byteOffset];
	glBufferData(pos_bufferview.target, pos_bufferview.byteLength, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	data = (void*)&model.buffers[index_bufferview.buffer].data[index_bufferview.byteOffset];
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_bufferview.byteLength, data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, pos_accessor.type, GL_FLOAT, GL_FALSE, pos_accessor.type * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void parts::draw() {
	glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_SHORT, 0);
}