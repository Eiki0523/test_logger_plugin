#include <windows.h>

#include "aviutl2_sdk/plugin2.h"

namespace {

HOST_APP_TABLE* g_host = nullptr;
EDIT_HANDLE* g_edit_handle = nullptr;
HINSTANCE g_instance = nullptr;
const wchar_t* g_pending_message = nullptr;

void log_callback(EDIT_SECTION* edit) {
	if (edit && edit->output_log && g_pending_message) {
		edit->output_log(g_pending_message);
	}
}

void log_message(const wchar_t* message) {
	if (!g_edit_handle) {
		return;
	}
	g_pending_message = message;
	g_edit_handle->call_edit_section(log_callback);
	g_pending_message = nullptr;
}

void project_load_handler(PROJECT_FILE*) {
	log_message(L"[test_logger] プロジェクトを読み込みました");
}

} // namespace

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID) {
	if (reason == DLL_PROCESS_ATTACH) {
		g_instance = instance;
		DisableThreadLibraryCalls(instance);
	}
	return TRUE;
}

extern "C" __declspec(dllexport) BOOL InitializePlugin(DWORD) {
	return TRUE;
}

extern "C" __declspec(dllexport) void UninitializePlugin() {
	g_host = nullptr;
	g_edit_handle = nullptr;
}

extern "C" __declspec(dllexport) BOOL RegisterPlugin(HOST_APP_TABLE* host) {
	g_host = host;
	if (!g_host) {
		return FALSE;
	}

	g_host->set_plugin_information(L"Test Logger Plugin 0.1");

	g_edit_handle = g_host->create_edit_handle();
	if (!g_edit_handle) {
		g_host = nullptr;
		return FALSE;
	}

	log_message(L"[test_logger] プラグインを読み込みました");

	g_host->register_project_load_handler(project_load_handler);

	return TRUE;
}
