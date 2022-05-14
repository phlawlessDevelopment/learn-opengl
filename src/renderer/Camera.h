#pragma once
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

class OrthographicCamera {
    public:
        OrthographicCamera(float left,float right, float top, float bottom);
        const glm::vec3& GetPosition() const { return m_Position; }
        const float& GetRotation() const { return m_Rotation; }

        void SetPosition(glm::vec3& pos){ m_Position = pos;}
        void SetPosition(float& zRot){ m_Rotation = zRot;}
        void UpdateProjectionMatrix(float left,float right, float top, float bottom);
        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }


    private:
        void RecalculateViewMatrix();
    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position;
        float m_Rotation = 0.0f;
};
