#include "CubeMaps.h"
#include "CommonFunction.h"

CubeMaps::CubeMaps() {

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
   // -------------------------
    Shader ourShader("D:/C++Projects/LJEngine/LJEngineThirdpartyLibrary/Shaders/6.2.cubemaps.vs", "D:/C++Projects/LJEngine/LJEngineThirdpartyLibrary/Shaders/6.2.cubemaps.fs");
    Shader skyboxShader("D:/C++Projects/LJEngine/LJEngineThirdpartyLibrary/Shaders/6.2.skybox.vs", "D:/C++Projects/LJEngine/LJEngineThirdpartyLibrary/Shaders/6.2.skybox.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
   // ------------------------------------------------------------------
    // load models
    // -----------
    Model ourModel("D:/Models/nanosuit/nanosuit.obj");

    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    for (float* p = skyboxVertices; p <= &skyboxVertices[sizeof(skyboxVertices) / sizeof(skyboxVertices[0]) - 1]; p++)
    {
        *p = *p * 4.0;
    }

    //for (int i : skyboxVertices)
    //{
    //    skyboxVertices[i] = skyboxVertices[i] * 2;
    //}

    // cube VAO
    //unsigned int cubeVAO, cubeVBO;
    //glGenVertexArrays(1, &cubeVAO);
    //glGenBuffers(1, &cubeVBO);
    //glBindVertexArray(cubeVAO);
    //glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // skybox VAO
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // load textures
   // -------------
    vector<std::string> faces
    {
        "D:/C++Projects/LJEngine/LJEngineResources/Textures/right.jpg",
        "D:/C++Projects/LJEngine/LJEngineResources/Textures/left.jpg",
        "D:/C++Projects/LJEngine/LJEngineResources/Textures/top.jpg",
        "D:/C++Projects/LJEngine/LJEngineResources/Textures/bottom.jpg",
        "D:/C++Projects/LJEngine/LJEngineResources/Textures/front.jpg",
        "D:/C++Projects/LJEngine/LJEngineResources/Textures/back.jpg",
    };
    unsigned int cubemapTexture = CommonFunction::GetInstance()->loadCubemap(faces);

    // shader configuration
    // --------------------
    ourShader.use();


    ourShader.setInt("skybox", 0);

    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);

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
        ourShader.setVec3("cameraPos", CommonFunction::GetInstance()->GetCamera().Position);
        // cubes
        //glBindVertexArray(cubeVAO);
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //glBindVertexArray(0);

        ourModel.Draw(ourShader);

        // draw skybox as last
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.use();
        view = glm::mat4(glm::mat3(CommonFunction::GetInstance()->GetCamera().GetViewMatrix())); // remove translation from the view matrix
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default

        CommonFunction::GetInstance()->RenderEditorUI();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(CommonFunction::GetInstance()->window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    //glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &skyboxVAO);
    //glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &skyboxVAO);

    //run the Editor UI 
    CommonFunction::GetInstance()->CleanupEditorUI();

    glfwTerminate();

}
