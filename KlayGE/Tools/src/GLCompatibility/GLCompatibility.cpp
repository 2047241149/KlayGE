#include <KlayGE/KlayGE.hpp>
#include <KFL/Math.hpp>
#include <KlayGE/Context.hpp>
#include <KFL/ResLoader.hpp>
#include <KlayGE/RenderFactory.hpp>
#include <KlayGE/RenderEngine.hpp>
#include <KlayGE/App3D.hpp>
#include <KlayGE/RenderSettings.hpp>
#include <KlayGE/Script.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace KlayGE;

namespace
{
	class information
	{
	public:
		information()
		{
			RenderEngine& re = Context::Instance().RenderFactoryInstance().RenderEngineInstance();

			re.GetCustomAttrib("VENDOR", &vendor_);
			re.GetCustomAttrib("RENDERER", &renderer_);

			std::string glsl_ver_str;
			re.GetCustomAttrib("SHADING_LANGUAGE_VERSION", &glsl_ver_str);
			if (!glsl_ver_str.empty())
			{
				std::string::size_type const glsl_dot_pos = glsl_ver_str.find(".");
				glsl_major_ver_ = glsl_ver_str[glsl_dot_pos - 1] - '0';
				glsl_minor_ver_ = glsl_ver_str[glsl_dot_pos + 1] - '0';
			}
			else
			{
				glsl_major_ver_ = 0;
				glsl_minor_ver_ = 0;
			}

			int num_exts;
			re.GetCustomAttrib("NUM_FEATURES", &num_exts);
			for (int i = 0; i < num_exts; ++ i)
			{
				std::ostringstream oss;
				oss << "FEATURE_NAME_" << i;

				std::string name;
				re.GetCustomAttrib(oss.str(), &name);
				std::string::size_type p = name.find("GL_VERSION_");
				if (std::string::npos == p)
				{
					extensions_.push_back(name);
				}
				else
				{
					major_ver_ = name[11] - '0';
					minor_ver_ = name[13] - '0';
				}
			}
		}

		std::vector<PyObjectPtr> store_to_py()
		{
			std::vector<PyObjectPtr> ret;

			ret.push_back(CppType2PyObjectPtr(vendor_));
			ret.push_back(CppType2PyObjectPtr(renderer_));
			ret.push_back(CppType2PyObjectPtr(major_ver_));
			ret.push_back(CppType2PyObjectPtr(minor_ver_));
			ret.push_back(CppType2PyObjectPtr(glsl_major_ver_));
			ret.push_back(CppType2PyObjectPtr(glsl_minor_ver_));

			std::string ext_str;
			for (std::vector<std::string>::const_iterator iter = extensions_.begin();
					iter != extensions_.end(); ++ iter)
			{
				ext_str += *iter + ' ';
			}
			ret.push_back(CppType2PyObjectPtr(ext_str));

			return ret;
		}

	private:
		std::string vendor_;
		std::string renderer_;

		int major_ver_;
		int minor_ver_;

		int glsl_major_ver_;
		int glsl_minor_ver_;

		std::vector<std::string> extensions_;
	};
}

class EmptyApp : public KlayGE::App3DFramework
{
public:
	EmptyApp()
		: App3DFramework("GL Compatibility")
	{
	}

	void DoUpdateOverlay()
	{
	}

	uint32_t DoUpdate(uint32_t /*pass*/)
	{
		return URV_Finished;
	}
};

int main()
{
	using namespace KlayGE;

	ResLoader::Instance().AddPath("../../../bin");

	Context::Instance().LoadCfg("KlayGE.cfg");
	ContextCfg context_cfg = Context::Instance().Config();
	context_cfg.render_factory_name = "OpenGL";
	context_cfg.graphics_cfg.hdr = false;
	Context::Instance().Config(context_cfg);

	EmptyApp app;
	app.Create();

	information info;
	std::vector<PyObjectPtr> for_py = info.store_to_py();

	ScriptEngine scriptEng;
	ScriptModule module("GLCompatibility");

	module.Call("gl_compatibility", &for_py.front(), &for_py.back() + 1);

	return 0;
}
