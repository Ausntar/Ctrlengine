#include "CteVulkan.hpp"
using namespace cte;
namespace cte {
	void CteVulkan::initVulkan(std::string ApplicationName) {
        createInstance();
	}
    void CteVulkan::cleanup() {
        vkDestroyInstance(instance, nullptr);
    }

}
