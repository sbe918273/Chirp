#include "pch.h"

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

	int w;
	int h;
	int comp;
	unsigned char* image = stbi_load("gold-dollar.png", &w, &h, &comp, STBI_rgb_alpha);

	float red = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(red, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Choose mipmap level.");
		ImGui::SliderFloat("mipLevel", &red, 0.0f, 1.0f);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glFlush();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

}