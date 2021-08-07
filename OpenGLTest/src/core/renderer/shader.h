#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Core
{
	struct ShaderProgramSource {
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader {
	private:
		std::string _filepath;
		unsigned int _rendererId;
		std::unordered_map<std::string, int> _uniformLocationCache;
	public:
		Shader(const std::string& filepath);
		~Shader();

		void set() const;
		void unset() const;

		void setUniform1i(const std::string& name, int value);
		void setUniform1f(const std::string& name, float value);
		void setUniformVec3(const std::string& name, float f0, float f1, float f2);
		void setUniformVec3(const std::string& name, glm::vec3 v);
		void setUniformVec4(const std::string& name, float f0, float f1, float f2, float f3);
		void setUniformMat4(const std::string& name, glm::mat4 value);
	private:
		unsigned int compileShader(unsigned int type, const std::string& source);
		unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
		ShaderProgramSource parseShader(const std::string& filepath);
		int getUniformLocation(const std::string& name);
	};
}
