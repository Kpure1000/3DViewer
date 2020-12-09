#include"render/Shader.h"

#ifndef GET_PROPERTY_ID(NAME)
#define GET_PROPERTY_ID(NAME) glGetUniformLocation(m_ID, (NAME).c_str())
#endif // !GET_PROPERTY_ID(NAME)


namespace rtx
{
	namespace render
	{

		Shader::Shader() :m_ID(-1)
		{
		}

		Shader::Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath)
		{

#pragma region load shader code from file

			char* vshaderCode;
			char* fshaderCode;
			std::ifstream vertIn;
			std::ifstream fragIn;
			std::string vstr, fstr;
			vertIn.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			fragIn.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try
			{
				vertIn.open(vertexShaderPath);
				fragIn.open(fragmentShaderPath);
				std::stringstream vstream, fstream;
				vstream << vertIn.rdbuf();
				fstream << fragIn.rdbuf();
				vertIn.close();
				fragIn.close();
				vstr = vstream.str();
				fstr = fstream.str();
			}
			catch (std::ifstream::failure e)
			{
				std::cerr << e.what() << std::endl;
			}
			vshaderCode = (char*)vstr.c_str();
			fshaderCode = (char*)fstr.c_str();

#pragma endregion

#pragma region vertex shader

			//  cerate vertex shader
			unsigned int vShader;
			vShader = glCreateShader(GL_VERTEX_SHADER);
			//  load shader code

			glShaderSource(vShader, 1, &vshaderCode, NULL);
			//  compile code
			glCompileShader(vShader);
			int success;
			char infoLog[512];
			glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(vShader, 512, NULL, infoLog);
				std::cerr << "\n>>>>>>>>>>>>\nSHADER::VERTEX::COMPILATION_FAILED, in File: " 
					<< vertexShaderPath << ". Error Info: \n" << infoLog << ">>>>>>>>>>>>\n";
			}

#pragma endregion

#pragma region fragment shader

			//  cerate fragment shader
			unsigned int fShader;
			fShader = glCreateShader(GL_FRAGMENT_SHADER);
			//  load shader code

			glShaderSource(fShader, 1, &fshaderCode, NULL);
			//  compile 
			glCompileShader(fShader);
			char finfoLog[512];
			glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(fShader, 512, NULL, finfoLog);
				std::cerr << "\n>>>>>>>>>>>>\nSHADER::FRAGMENT::COMPILATION_FAILED, in File: "
					<< fragmentShaderPath << ". Error Info: \n" << finfoLog << ">>>>>>>>>>>>\n";
			}

#pragma endregion

#pragma region shader program

			m_ID = glCreateProgram();
			//  add shader to program
			glAttachShader(m_ID, vShader);
			glAttachShader(m_ID, fShader);
			//  link shaders from program
			glLinkProgram(m_ID);

			char pinfoLog[512];
			glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(m_ID, 512, NULL, pinfoLog);
				std::cerr << "\n>>>>>>>>>>>>\nSHADER::PROGRAM::LINK_FAILED, Error Info:\n"
					<< pinfoLog << ">>>>>>>>>>>>\n";
			}

			//  release shaders
			glDeleteShader(vShader);
			glDeleteShader(fShader);

#pragma endregion

		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ID);
		}

		int Shader::GetID() const
		{
			return m_ID;
		}

		void Shader::Use() const
		{
			glUseProgram(m_ID);
		}

		void Shader::SetBool(const std::string& name,
			const bool& value) const
		{
			SetInt(name, value);
		}

		void Shader::SetInt(const std::string& name,
			const int& value) const
		{
			glUniform1i(GET_PROPERTY_ID(name), value);
		}

		void Shader::SetFloat(const std::string& name,
			const float& value) const
		{
			glUniform1f(GET_PROPERTY_ID(name), value);
		}

		void Shader::SetVector2(const std::string& name,
			const glm::vec2& value) const
		{
			glUniform2f(GET_PROPERTY_ID(name), value.x, value.y);
		}

		void Shader::SetVector3(const std::string& name,
			const glm::vec3& value) const
		{
			glUniform3f(GET_PROPERTY_ID(name), value.x, value.y, value.z);
		}

		void Shader::SetVector4(const std::string& name,
			const glm::vec4& value)const
		{
			glUniform4f(GET_PROPERTY_ID(name), value.x, value.y, value.z, value.w);
		}

		void Shader::SetRGBA(const std::string& name, const util::Color& color) const
		{
			SetVector4(name, color.RGBA());
		}

		void Shader::SetRGB(const std::string& name, const util::Color& color) const
		{
			SetVector3(name, color.RGB());

		}
		void Shader::SetMatrix4(const std::string& name, const glm::mat4 mat) const
		{
			glUniformMatrix4fv(GET_PROPERTY_ID(name), 1, GL_FALSE, glm::value_ptr(mat));
		}

		void Shader::SetSampler2D(const std::string& name, const Texture& texture) const
		{
			glUniform1i(GET_PROPERTY_ID(name), texture.GetIndex()); //  ÷∂Ø…Ë÷√
		}

		void Shader::SetArray(const std::string& name,const int& size, const float* data)const
		{
			glUniform1fv(GET_PROPERTY_ID(name), size, data);
		}

	}
}