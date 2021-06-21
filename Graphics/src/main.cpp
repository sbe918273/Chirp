#include "pch.h"
#include "Shader.h"
#include "VertexArray.h"

int main()
{
	std::cout << "Humble Beginnings";
	glfwInit();

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Watch this space!", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	glewInit();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 440");

	std::vector<std::string> shaderFiles[2] = 
	{
		{ "res/shaders/test/VertexTest.glsl", "res/shaders/test/VertexAddOn.glsl" },
		{ "res/shaders/test/FragmentTest.glsl" }
	};
	ShaderMap::ShaderType shaderTypes[2] = { ShaderMap::ShaderType::VERTEX, ShaderMap::ShaderType::FRAGMENT };
	Shader solidProgram(2, shaderFiles, shaderTypes);
	solidProgram.use();

	int w, h, channelCount;
	unsigned char* image = stbi_load("gold-dollar.png", &w, &h, &channelCount, STBI_rgb_alpha);

	float pos[8] =
	{
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	unsigned int indices[6] =
	{
		0, 1, 2,
		2, 3, 0
	};


	Buffer eb(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), GL_STATIC_DRAW, indices);
	Buffer vb(GL_ARRAY_BUFFER, 8 * sizeof(float), GL_STATIC_DRAW, pos);

	VertexArray va;
	va.SetElementBuffer(eb);
	std::vector<VertexAttrib> attribs = { {2, DataMap::DataType::FLOAT} };
	va.AddVertexBuffer(0, vb, attribs);

	//GLuint vb; glGenBuffers(1, &vb); glBindBuffer(GL_ARRAY_BUFFER, vb); glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), pos, GL_STATIC_DRAW);
	//GLuint va; glGenVertexArrays(1, &va); glBindVertexArray(va); glEnableVertexAttribArray(0); glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), 0);
	//GLuint eb; glGenBuffers(1, &eb); glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb); glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	float red = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(red, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Choose red component");
		ImGui::SliderFloat("red", &red, 0.0f, 1.0f);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		va.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glFlush();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

}