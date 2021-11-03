#include "Geometry_shader_exploding.h"
#include "CommonFunction.h"

Geometry_shader_exploding::Geometry_shader_exploding() {

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader ourShader("D:/C++Projects/LJEngine/LJEngineThirdpartyLibrary/Shaders/9.2.geometry_shader.vs", 
                     "D:/C++Projects/LJEngine/LJEngineThirdpartyLibrary/Shaders/9.2.geometry_shader.fs", 
                     "D:/C++Projects/LJEngine/LJEngineThirdpartyLibrary/Shaders/9.2.geometry_shader.gs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // load models
    // -----------
    Model ourModel("D:/Models/nanosuit/nanosuit.obj");

    // render loop
// -----------
    while (!glfwWindowShouldClose(CommonFunction::GetInstance()->GetWindow()))
    {
        //run the Editor UI 
        CommonFunction::GetInstance()->UIRuningMainLoop();

        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        CommonFunction::GetInstance()->SetDeltaTime(currentFrame - CommonFunction::GetInstance()->GetLastFrame());
        CommonFunction::GetInstance()->SetLastFrame(currentFrame);

        // input
        // -----
        CommonFunction::GetInstance()->processInput(CommonFunction::GetInstance()->GetWindow());

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw scene as normal
        ourShader.use();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(CommonFunction::GetInstance()->engineEditor.GetPosition()[0],
            CommonFunction::GetInstance()->engineEditor.GetPosition()[1],
            CommonFunction::GetInstance()->engineEditor.GetPosition()[2])); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(CommonFunction::GetInstance()->engineEditor.GetScale()[0],
            CommonFunction::GetInstance()->engineEditor.GetScale()[1],
            CommonFunction::GetInstance()->engineEditor.GetScale()[2])); // it's a bit too big for our scene, so scale it down
        glm::mat4 view = CommonFunction::GetInstance()->GetCamera().GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(CommonFunction::GetInstance()->GetCamera().Zoom), (float)CommonFunction::GetInstance()->GetSCR_WIDTH() / (float)CommonFunction::GetInstance()->GetSCR_HEIGHT(), 0.1f, 10000.0f);
        ourShader.setMat4("model", model);
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);

        // add time component to geometry shader in the form of a uniform
        ourShader.setFloat("time", glfwGetTime());

        // draw model
        ourModel.Draw(ourShader);

        CommonFunction::GetInstance()->RenderEditorUI();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(CommonFunction::GetInstance()->window);
        glfwPollEvents();
    }

    //run the Editor UI 
    CommonFunction::GetInstance()->CleanupEditorUI();
    glfwTerminate();

}
