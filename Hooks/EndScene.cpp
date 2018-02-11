#include "../Cheat.h"
#include "Menu.h"
#include "../Parser.h"
#include "../SkinChanger.h"
#include "../ImGUI/imgui_internal.h"
#include "../ImGUI/imgui.h"
#include <locale>

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

float clip(float n, float lower, float upper)
{
	n = (n > lower) * n + !(n > lower) * lower;
	return (n < upper) * n + !(n < upper) * upper;
}

static constexpr auto ALPHA_FREQ = 255 / 0.55f;
static constexpr auto ALPHA_FREQUENCY = 1 / 0.55f;
static constexpr auto POS_FREQUENCY = 398 / 0.55f;

void GUI_Init(IDirect3DDevice9* pDevice);

void color()
{
	auto bColor = Vars.g_fBColor;
	auto mColor = Vars.g_fMColor;
	auto tColor = Vars.g_fTColor;

	ImColor mainColor = ImColor(int(15), int(135), int(105), 255);
	ImColor bodyColor = ImColor(int(24), int(24), int(24), 255);
	ImColor fontColor = ImColor(int(255), int(255), int(255), 255);

	ImGuiStyle& style = ImGui::GetStyle();

	ImVec4 mainColorHovered = ImVec4(mainColor.Value.x + 0.1f, mainColor.Value.y + 0.1f, mainColor.Value.z + 0.1f, mainColor.Value.w);
	ImVec4 mainColorActive = ImVec4(mainColor.Value.x + 0.2f, mainColor.Value.y + 0.2f, mainColor.Value.z + 0.2f, mainColor.Value.w);
	ImVec4 menubarColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w - 0.8f);
	ImVec4 frameBgColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w + .1f);
	ImVec4 tooltipBgColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w + .05f);

	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(8, 8);
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowRounding = 0.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.ChildWindowRounding = 0.0f;
	style.FramePadding = ImVec2(4, 3);
	style.FrameRounding = 2.0f;
	style.ItemSpacing = ImVec2(4, 3);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 3.0f;
	style.ScrollbarSize = 8.f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 1.0f;
	style.GrabRounding = 0.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.DisplayWindowPadding = ImVec2(22, 22);
	style.DisplaySafeAreaPadding = ImVec2(4, 4);
	style.AntiAliasedLines = true;
	style.AntiAliasedShapes = true;
	style.CurveTessellationTol = 1.25f;

	style.Colors[ImGuiCol_Text] = fontColor;

	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = bodyColor;
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(.0f, .0f, .0f, .0f);
	style.Colors[ImGuiCol_PopupBg] = tooltipBgColor;
	style.Colors[ImGuiCol_Border] = ImColor(200, 200, 200, 220);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = frameBgColor;
	style.Colors[ImGuiCol_FrameBgHovered] = mainColorHovered;
	style.Colors[ImGuiCol_FrameBgActive] = mainColorActive;
	style.Colors[ImGuiCol_TitleBg] = mainColor;
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = mainColor;
	style.Colors[ImGuiCol_MenuBarBg] = menubarColor;
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(frameBgColor.x + .05f, frameBgColor.y + .05f, frameBgColor.z + .05f, frameBgColor.w);
	style.Colors[ImGuiCol_ScrollbarGrab] = mainColor;
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = mainColorActive;
	style.Colors[ImGuiCol_ComboBg] = frameBgColor;
	style.Colors[ImGuiCol_CheckMark] = mainColor;
	style.Colors[ImGuiCol_SliderGrab] = mainColorHovered;
	style.Colors[ImGuiCol_SliderGrabActive] = mainColorActive;
	style.Colors[ImGuiCol_Button] = mainColor;
	style.Colors[ImGuiCol_ButtonHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ButtonActive] = mainColorActive;
	style.Colors[ImGuiCol_Header] = mainColor;
	style.Colors[ImGuiCol_HeaderHovered] = mainColorHovered;
	style.Colors[ImGuiCol_HeaderActive] = mainColorActive;

	style.Colors[ImGuiCol_Column] = mainColor;
	style.Colors[ImGuiCol_ColumnHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ColumnActive] = mainColorActive;

	style.Colors[ImGuiCol_ResizeGrip] = mainColor;
	style.Colors[ImGuiCol_ResizeGripHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ResizeGripActive] = mainColorActive;
	style.Colors[ImGuiCol_CloseButton] = mainColor;
	style.Colors[ImGuiCol_CloseButtonHovered] = mainColorHovered;
	style.Colors[ImGuiCol_CloseButtonActive] = mainColorActive;
	style.Colors[ImGuiCol_PlotLines] = mainColor;
	style.Colors[ImGuiCol_PlotLinesHovered] = mainColorHovered;
	style.Colors[ImGuiCol_PlotHistogram] = mainColor;
	style.Colors[ImGuiCol_PlotHistogramHovered] = mainColorHovered;
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}

char* KeyStrings[254] = { "No key", "Left Mouse", "Right Mouse", "Control+Break", "Middle Mouse", "Mouse 4", "Mouse 5",
nullptr, "Backspace", "TAB", nullptr, nullptr, nullptr, "ENTER", nullptr, nullptr, "SHIFT", "CTRL", "ALT", "PAUSE",
"CAPS LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "ESC", nullptr, nullptr, nullptr, nullptr, "SPACEBAR",
"PG UP", "PG DOWN", "END", "HOME", "Left", "Up", "Right", "Down", nullptr, "Print", nullptr, "Print Screen", "Insert",
"Delete", nullptr, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X",
"Y", "Z", "Left Windows", "Right Windows", nullptr, nullptr, nullptr, "NUM 0", "NUM 1", "NUM 2", "NUM 3", "NUM 4", "NUM 5", "NUM 6",
"NUM 7", "NUM 8", "NUM 9", "*", "+", "_", "-", ".", "/", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
"F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24", nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, "NUM LOCK", "SCROLL LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, "LSHIFT", "RSHIFT", "LCONTROL", "RCONTROL", "LMENU", "RMENU", nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "Next Track", "Previous Track", "Stop", "Play/Pause", nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, ";", "+", ",", "-", ".", "/?", "~", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "[{", "\\|", "}]", "'\"", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

std::vector<std::string> configs;

void GetConfigMassive()
{
	//get all files on folder

	configs.clear();

	static char path[MAX_PATH];
	std::string szPath1;

	if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
		return;

	szPath1 = std::string(path) + XorStr("\\WRS\\*");


	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	configs.push_back("default.ini");

	hf = FindFirstFile(szPath1.c_str(), &FindFileData);
	if (hf != INVALID_HANDLE_VALUE) {
		do {
			std::string filename = FindFileData.cFileName;

			if (filename == ".")
				continue;

			if (filename == "..")
				continue;

			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				if (filename.find(".ini") != std::string::npos)
				{
					configs.push_back(std::string(filename));
				}
			}
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
}

namespace Tabs
{
	//size = 800, Windowpadding = 8,8
	void RageTab()
	{
		switch (Vars.Menu.iRageSubTab)
		{
		case 0:
		{
			ImGui::Button("RAGEBOT - MAIN", ImVec2(784, 25));
			ImGui::BeginChild("linke seite", ImVec2(390, 384), true);

			{
				ImGui::Button("Aimbot", ImVec2(372, 25));

				ImGui::Columns(2, nullptr, false);
				ImGui::SetColumnOffset(1, 200);
				ImGui::Checkbox(XorStr("Ragebot Enabled"), &Vars.Ragebot.Enabled);
				ImGui::Checkbox(XorStr("Anti-Untrusted"), &Vars.Ragebot.UntrustedCheck);
				ImGui::Text(XorStr("FOV"));
				ImGui::SameLine();
				ImGui::SliderFloat(XorStr("FOV"), &Vars.Ragebot.FOV, 1.f, 360.f, "%.0f");
				ImGui::Checkbox(XorStr("Friendly Fire"), &Vars.Ragebot.FriendlyFire);
				ImGui::Checkbox(XorStr("Auto Fire"), &Vars.Ragebot.AutoFire);
				ImGui::Checkbox(XorStr("AutoPistol"), &Vars.Ragebot.AutoPistol);
				ImGui::Checkbox(XorStr("Silent"), &Vars.Ragebot.Silent);
				ImGui::Checkbox(XorStr("pSilent"), &Vars.Ragebot.pSilent);
				ImGui::Text(XorStr("Recoil"));
				ImGui::SameLine();
				ImGui::Combo(XorStr("##RCSTYPE"), &Vars.Ragebot.RCS, XorStr("Off\0\rRemove Recoil\0\0"), -1);
			}ImGui::EndChild();

			ImGui::SameLine();

			ImGui::BeginChild("rechte seite", ImVec2(390, 384), true);
			{
				ImGui::Button("Selection", ImVec2(372, 25));
				//ImGui::Combo(XorStr("Hitbox"), &Vars.Ragebot.Hitbox, XorStr("PELVIS\0\r\0\r\0\rHIP\0\rLOWER SPINE\0\rMIDDLE SPINE\0\rUPPER SPINE\0\rNECK\0\rHEAD\0\0"), -1);
				ImGui::Combo(XorStr("Hitbox"), &Vars.Ragebot.Hitbox, XorStr("PELVIS\0\rHIP\0\rLOWER SPINE\0\rMIDDLE SPINE\0\rUPPER SPINE\0\rNECK\0\rHEAD\0\0"), -1);

				ImGui::Combo(XorStr("HitScan"), &Vars.Ragebot.HitScan, charenc("Off\0\rSelected\0\0"), -1);
				ImGui::Checkbox(XorStr("MultiPoint"), &Vars.Ragebot.MultiPoints);
				ImGui::Text(XorStr("Scale"));
				ImGui::SameLine();
				ImGui::SliderFloat(XorStr("##MultiPointscale"), &Vars.Ragebot.PointScale, 0.f, 1.f, "%.01f");
				ImGui::Checkbox(XorStr("Autowall"), &Vars.Ragebot.AutoWall);

				ImGui::Text(XorStr("HitScan Bones"));
				ImGui::Selectable(XorStr("Head"), &Vars.Ragebot.bones[HITBOX_HEAD], 0, ImVec2(93.f, 20.f));
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(XorStr("HitScan head"));

				ImGui::SameLine();

				ImGui::Selectable(XorStr("Neck"), &Vars.Ragebot.bones[HITBOX_NECK], 0, ImVec2(93.f, 20.f));
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(XorStr("HitScan neck"));

				ImGui::SameLine();

				ImGui::Selectable(XorStr("Pelvis"), &Vars.Ragebot.bones[HITBOX_PELVIS], 0, ImVec2(93.f, 20.f));
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(XorStr("HitScan pelvis"));


				ImGui::Selectable(XorStr("Spine"), &Vars.Ragebot.bones[HITBOX_SPINE], 0, ImVec2(93.f, 20.f));
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(XorStr("HitScan spine"));

				ImGui::SameLine();

				ImGui::Selectable(XorStr("Legs"), &Vars.Ragebot.bones[HITBOX_LEGS], 0, ImVec2(93.f, 20.f));
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(XorStr("HitScan legs"));

				ImGui::SameLine();

				ImGui::Selectable(XorStr("Arms"), &Vars.Ragebot.bones[HITBOX_ARMS], 0, ImVec2(93.f, 20.f));
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(XorStr("HitScan arms"));
			}ImGui::EndChild();
			break;
		}
		case 1:
		{
			ImGui::Button("RAGEBOT - HvH", ImVec2(784, 25));
			ImGui::BeginChild("linke seite", ImVec2(390, 384), true);
			{
				ImGui::Button("Resolver", ImVec2(372, 25));

				ImGui::Columns(2, nullptr, false);
				ImGui::SetColumnOffset(1, 200);
				ImGui::Combo(XorStr("Resolver"), &Vars.Ragebot.Antiaim.Resolver, XorStr("Disabled\0\rDynamic\0\rBruteforce\0\0"), -1);
				ImGui::Combo(XorStr("Adjust"), &Vars.Ragebot.ResolverHelper, XorStr("No\0\rBeta\0\rBeta\0\rNormal\0\0"), -1);

				ImGui::Checkbox(XorStr("Auto Stop"), &Vars.Ragebot.AutoStop);
				ImGui::Checkbox(XorStr("Auto Crouch"), &Vars.Ragebot.AutoCrouch);
				ImGui::Checkbox(XorStr("Auto Scope"), &Vars.Ragebot.AutoScope);
			}ImGui::EndChild();

			ImGui::SameLine();

			ImGui::BeginChild("rechte seite", ImVec2(390, 384), true);
			{
				ImGui::Button("Hit and Dmg", ImVec2(372, 25));
				ImGui::Checkbox(XorStr("Hit Chance"), &Vars.Ragebot.HitChance);
				ImGui::Text(XorStr("HitChance"));
				ImGui::SameLine();
				ImGui::SliderFloat(XorStr("##HCAmount"), &Vars.Ragebot.HitChanceAmt, 1.f, 100.f, "%.1f");

				ImGui::Text(XorStr("Min Dmg"));
				ImGui::SameLine();
				ImGui::SliderFloat(XorStr("##MinDamage"), &Vars.Ragebot.AutoWallDmg, 0.1f, 120.f, "%.1f");
			}ImGui::EndChild();
			break;
		}
		case 2:
		{
			ImGui::Button("RAGEBOT - Anti-Aim", ImVec2(784, 25));
			ImGui::BeginChild("linke seite", ImVec2(390, 384), true);
			{
				ImGui::Button("Pitch and Yaw", ImVec2(372, 25));

				ImGui::Columns(2, nullptr, false);
				ImGui::SetColumnOffset(1, 200);
				ImGui::Checkbox(XorStr("Enabled"), &Vars.Ragebot.Antiaim.Enabled);
				ImGui::Checkbox(XorStr("Fake Yaw"), &Vars.Ragebot.Antiaim.FakeYaw);
				ImGui::Checkbox(XorStr("At Target"), &Vars.Ragebot.Antiaim.AtPlayer);
				ImGui::Combo(XorStr("Pitch"), &Vars.Ragebot.Antiaim.Pitch, charenc("Unselected\0\rUP\0\rDOWN\0\rJITTER\0\rZERO\0\rEmotion\0\rDOWN JITTER\0\rDOWN2\0\0"), -1);
				ImGui::Combo(XorStr("Yaw"), &Vars.Ragebot.Antiaim.YawReal, charenc("Unselected\0\rSPIN\0\rDestroy LBY\0\rSIDEWAYS1\0\rSIDEWAYS2\0\rBACKWARDS\0\rLEFT\0\rRIGHT\0\rZERO\0\rFAKESPIN\0\rLowerBody Based\0\rLag FAKESPIN\0\rMEMESPIN\0\rFAKE 3\0\0"), -1);

				ImGui::Combo(XorStr("Fake Yaw"), &Vars.Ragebot.Antiaim.YawFake, charenc("Unselected\0\rSPIN\0\rJITTER\0\rSIDEWAYS1\0\rSIDEWAYS2\0\rBACKWARDS\0\rLEFT\0\rRIGHT\0\rZERO\0\rFAKESPIN\0\rLowerBody Based\0\rLag FAKESPIN\0\rMEMESPIN\0\rFAKE 3\0\0"), -1);
				bool unt = Vars.Ragebot.UntrustedCheck;
				ImGui::Checkbox(XorStr("Custom Pitch"), &Vars.Ragebot.Antiaim.PitchCustom);
				ImGui::Checkbox(XorStr("Custom Yaw"), &Vars.Ragebot.Antiaim.YawCustom);
				ImGui::Text(XorStr("RealPitch"));
				ImGui::SliderFloat(XorStr("##REALPITCH"), &Vars.Ragebot.Antiaim.PCReal, unt ? -89 : -180, unt ? 89 : 180);
				ImGui::Text(XorStr("FakePitch"));
				ImGui::SliderFloat(XorStr("##FAKEPITCH"), &Vars.Ragebot.Antiaim.PCFake, unt ? -89 : -180, unt ? 89 : 180);
				ImGui::Text(XorStr("RealYaw"));
				ImGui::SliderFloat(XorStr("##RealYaw"), &Vars.Ragebot.Antiaim.YCReal, unt ? -179 : -360, unt ? 179 : 360);
				ImGui::Text(XorStr("FakeYaw"));
				ImGui::SliderFloat(XorStr("##FakeYaw"), &Vars.Ragebot.Antiaim.YCFake, unt ? -179 : -360, unt ? 179 : 360);
			}ImGui::EndChild();

			ImGui::SameLine();

			ImGui::BeginChild("rechte seite", ImVec2(390, 384), true);
			{
				ImGui::Button("Disables and Render", ImVec2(372, 25));
				ImGui::Checkbox(XorStr("On Knife"), &Vars.Ragebot.Antiaim.knife_held);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(XorStr("Stops your antiaim while you have your knife out."));
				ImGui::Checkbox(XorStr("No ESP"), &Vars.Ragebot.Antiaim.no_enemy);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(XorStr("Stops your antiaim when there are no enemies visible."));
				ImGui::Checkbox(XorStr("ThirdPerson"), &Vars.Visuals.thirdperson.enabled);
				ImGui::Checkbox(XorStr("LBY Indicator"), &Vars.Misc.Watermark);
				ImGui::Text(XorStr("Distance"));
				ImGui::SameLine();
				ImGui::SliderFloat(XorStr("##THRDPERSDIST"), &Vars.Visuals.thirdperson.distance, 30.f, 200.f, "%.0f");
			}ImGui::EndChild();
			break;
		}
		}
	}
	void LegitTab()
	{
		switch (Vars.Menu.iLegitSubTab)
		{
		case 0:
		{
			ImGui::Button("Legitbot - MAIN", ImVec2(784, 25));
			ImGui::BeginChild("linke seite", ImVec2(390, 384), true);

			{
				ImGui::Button("Aimbot", ImVec2(372, 25));

				ImGui::Columns(2, nullptr, false);
				ImGui::SetColumnOffset(1, 200);
				ImGui::Checkbox(XorStr("Enable Legit Aimbot"), &Vars.Legitbot.Aimbot.Enabled);
				ImGui::Checkbox(XorStr("Always on"), &Vars.Legitbot.Aimbot.AlwaysOn);
				ImGui::Combo(XorStr("Aimbot Key"), &Vars.Legitbot.Aimbot.Key, keyNames, IM_ARRAYSIZE(keyNames));
				ImGui::Checkbox(XorStr("Aim on Key"), &Vars.Legitbot.Aimbot.OnKey);
				ImGui::Checkbox(XorStr("Friendly Fire"), &Vars.Legitbot.Aimbot.FriendlyFire);
				ImGui::Checkbox(XorStr("Smoke Check"), &Vars.Legitbot.Aimbot.SmokeCheck);
				ImGui::Checkbox(XorStr("AutoPistol"), &Vars.Legitbot.Aimbot.AutoPistol);
				ImGui::Text(XorStr("Delay"));
				ImGui::SameLine();
				ImGui::SliderInt(XorStr("Delay"), &Vars.Legitbot.delay, 1, 100);

			}ImGui::EndChild();

			ImGui::SameLine();

			ImGui::BeginChild("rechte seite", ImVec2(390, 384), true);
			{
				ImGui::Button("Selection", ImVec2(372, 25));
				if (G::LocalPlayer->GetAlive() && G::LocalPlayer->GetWeapon()->IsGun()) {
					ImGui::Text("Current Weapon: %s", G::LocalPlayer->GetWeapon()->GetWeaponName().c_str());
					int curweapon = G::LocalPlayer->GetWeapon()->GetItemDefinitionIndex();
					ImGui::Checkbox(XorStr("pSilent Aim"), &Vars.Legitbot.Weapon[curweapon].pSilent);
					ImGui::Combo(XorStr("Hitbox"), &Vars.Legitbot.Weapon[curweapon].Hitbox, charenc("PELVIS\0\rHIP\0\rLOWER SPINE\0\rMIDDLE SPINE\0\rUPPER SPINE\0\rNECK\0\rHEAD\0\rNEAREST\0\0"), -1);
					if (Vars.Legitbot.Weapon[curweapon].pSilent)
						ImGui::Text(XorStr("FOV")); ImGui::SameLine();
						ImGui::SliderFloat(XorStr("pSilent FOV"), &Vars.Legitbot.Weapon[curweapon].PFOV, 0.1f, 3.f, "%.2f");
						ImGui::Text(XorStr("FOV"));
						ImGui::SameLine();
					ImGui::SliderFloat(XorStr("FOV"), &Vars.Legitbot.Weapon[curweapon].FOV, 0.1f, 50.f, "%.2f");
					if (!Vars.Legitbot.Weapon[curweapon].AdaptiveSmooth)
						ImGui::Text(XorStr("Smooth"));
					ImGui::SameLine();
						ImGui::SliderFloat(XorStr("Smooth"), &Vars.Legitbot.Weapon[curweapon].Speed, 0.1f, 100.f, "%.2f");
					if (!G::LocalPlayer->GetWeapon()->IsSniper()) {
						ImGui::Text(XorStr("RCS X"));
						ImGui::SameLine();
						ImGui::SliderFloat(XorStr("RCS X"), &Vars.Legitbot.Weapon[curweapon].RCSAmountX, 1.f, 100.f, "%.0f", 1.f);
						ImGui::Text(XorStr("RCS Y"));
						ImGui::SameLine();
						ImGui::SliderFloat(XorStr("RCS Y"), &Vars.Legitbot.Weapon[curweapon].RCSAmountY, 1.f, 100.f, "%.0f", 1.f);
					}
					//ImGui::Checkbox(XorStr("RCS Enabled"), &Vars.Legitbot.Weapon[curweapon].RCS);

					if (G::LocalPlayer->GetWeapon()->IsSniper()) {
						ImGui::Checkbox(XorStr("FastZoom"), &Vars.Legitbot.fastzoom);
						ImGui::SameLine();
						ImGui::Checkbox(XorStr("Switch wep"), &Vars.Legitbot.fastzoomswitch);
					}
				}
				else
				{
					ImGui::Text(XorStr("Invalid weapon/Isnt Alive"));
				}
			}ImGui::EndChild();
			break;
		}
		case 1:
		{
			ImGui::Button("Triggerbot - Main", ImVec2(784, 25));
			ImGui::BeginChild("linke seite", ImVec2(390, 384), true);
			{
				ImGui::Button("Setup Triggerbot", ImVec2(372, 25));

				ImGui::Columns(2, nullptr, false);
				ImGui::SetColumnOffset(1, 200);
				ImGui::Checkbox(XorStr("Enable Triggerbot"), &Vars.Legitbot.Triggerbot.Enabled);
				ImGui::Checkbox(XorStr("Ignore Key"), &Vars.Legitbot.Triggerbot.AutoFire);
				if (Vars.Legitbot.Triggerbot.AutoFire == false)
					ImGui::Combo(XorStr("Key"), &Vars.Legitbot.Triggerbot.Key, keyNames, IM_ARRAYSIZE(keyNames));
				ImGui::Checkbox(XorStr("Auto Wall"), &Vars.Legitbot.Triggerbot.AutoWall);
				ImGui::Checkbox(XorStr("Hit Chance"), &Vars.Legitbot.Triggerbot.HitChance);
			}ImGui::EndChild();

			ImGui::SameLine();

			ImGui::BeginChild("rechte seite", ImVec2(390, 384), true);
			{
				ImGui::Button("Selection", ImVec2(372, 25));
				ImGui::Text(XorStr("HitChance"));
				ImGui::SameLine();
				ImGui::SliderFloat(XorStr("Amount"), &Vars.Legitbot.Triggerbot.HitChanceAmt, 1.f, 100.f, "%.0f");
				ImGui::Text(XorStr("Delay"));
				ImGui::SameLine();
				ImGui::SliderInt(XorStr("Delay"), &Vars.Legitbot.Triggerbot.Delay, 1, 1000);
				ImGui::BeginChild(XorStr("Filter"), ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 19 * 6));
				{
					ImGui::Selectable(XorStr(" Head"), &Vars.Legitbot.Triggerbot.Filter.Head);
					ImGui::Selectable(XorStr(" Chest"), &Vars.Legitbot.Triggerbot.Filter.Chest);
					ImGui::Selectable(XorStr(" Stomach"), &Vars.Legitbot.Triggerbot.Filter.Stomach);
					ImGui::Selectable(XorStr(" Arms"), &Vars.Legitbot.Triggerbot.Filter.Arms);
					ImGui::Selectable(XorStr(" Legs"), &Vars.Legitbot.Triggerbot.Filter.Legs);
					ImGui::Selectable(XorStr(" Teammates"), &Vars.Legitbot.Triggerbot.Filter.Friendly);
				}ImGui::EndChild();
				break;
			}
		}
		}
	}
	void VisualsTab()
	{
		switch (Vars.Menu.iVisualsSubTab)
		{
		case 0:
		{
			ImGui::Button("ESP", ImVec2(784, 25));
			ImGui::BeginChild("linke seite", ImVec2(390, 384), true);

			{
				ImGui::Button("Drawing", ImVec2(372, 25));

				ImGui::Columns(2, nullptr, false);
				ImGui::SetColumnOffset(1, 200);
				ImGui::Combo(XorStr("Aimlines"), &Vars.Visuals.Line, XorStr("Off\0\rCentered\0\rBottom\0\0"), -1);
				ImGui::Checkbox(XorStr("Enable Visuals"), &Vars.Visuals.Enabled);
				ImGui::Checkbox(XorStr("2D Box"), &Vars.Visuals.Box);
				ImGui::Checkbox(XorStr("3D Box"), &Vars.Visuals.esp3d);
				ImGui::Checkbox(XorStr("Head Box"), &Vars.Visuals.bonebox);
				ImGui::Checkbox(XorStr("Skeleton"), &Vars.Visuals.Skeleton);
				ImGui::Checkbox(XorStr("Bullet Trace"), &Vars.Visuals.BulletTrace);
				ImGui::Checkbox(XorStr("Anti-Screenshot"), &Vars.Visuals.AntiSS);
			}ImGui::EndChild();

			ImGui::SameLine();

			ImGui::BeginChild("rechte seite", ImVec2(390, 384), true);
			{
				ImGui::Button("Filter", ImVec2(372, 25));
				ImGui::Selectable(XorStr(" Show Enemies"), &Vars.Visuals.Filter.Enemies);
				ImGui::Selectable(XorStr(" Show Teammates"), &Vars.Visuals.Filter.Friendlies);
				ImGui::Selectable(XorStr(" Show Dropped Weapons"), &Vars.Visuals.Filter.Weapons);
				ImGui::Selectable(XorStr(" Show Decoy"), &Vars.Visuals.Filter.Decoy);
				ImGui::Selectable(XorStr(" Show C4"), &Vars.Visuals.Filter.C4);
				ImGui::Selectable(XorStr(" Show Name"), &Vars.Visuals.InfoName);
				ImGui::Selectable(XorStr(" Show Health"), &Vars.Visuals.InfoHealth);
				ImGui::Selectable(XorStr(" Show Weapon"), &Vars.Visuals.InfoWeapon);
				ImGui::Selectable(XorStr(" Show If Flashed"), &Vars.Visuals.InfoFlashed);
			}ImGui::EndChild();
			break;
		}
		case 1:
		{
			ImGui::Button("Visuals - Rendering", ImVec2(784, 25));
			ImGui::BeginChild("linke seite", ImVec2(390, 384), true);
			{
				ImGui::Button("Rendering", ImVec2(372, 25));

				ImGui::Columns(2, nullptr, false);
				ImGui::SetColumnOffset(1, 200);
				ImGui::Checkbox(XorStr("Chams Enable"), &Vars.Visuals.Chams.Enabled);
				ImGui::Combo(XorStr("Mode"), &Vars.Visuals.Chams.Mode, XorStr("Flat\0\rTextured\0\0"), -1);
				ImGui::Checkbox(XorStr("XQZ"), &Vars.Visuals.Chams.XQZ);
				ImGui::Checkbox(XorStr("Hands"), &Vars.Visuals.Chams.hands);
				ImGui::Checkbox(XorStr("Weapon"), &Vars.Visuals.ChamsWeapon);
				ImGui::Checkbox(XorStr("Rainbow Hands"), &Vars.Visuals.Chams.RainbowHands);
				ImGui::Text(XorStr("Speed"));
				ImGui::SameLine();
				ImGui::SliderFloat(XorStr("##CHMSSpeed"), &Vars.Visuals.Chams.RainbowTime, 1.f, 150.f, "%.0f");
			}ImGui::EndChild();

			ImGui::SameLine();

			ImGui::BeginChild("rechte seite", ImVec2(390, 384), true);
			{
				ImGui::Button("Rage", ImVec2(372, 25));
				ImGui::Checkbox(XorStr("No Vis Recoil"), &Vars.Visuals.RemovalsVisualRecoil);
				ImGui::Checkbox(XorStr("No Flash"), &Vars.Visuals.RemovalsFlash);
				ImGui::Checkbox(XorStr("No Scope"), &Vars.Visuals.NoScope);
				ImGui::Text(XorStr("Override Fov"));
				ImGui::SameLine();
				ImGui::SliderInt(XorStr("##OverrideFov"), &Vars.Misc.fov, -70, 70);
			}ImGui::EndChild();
			break;
		}
		case 2:
		{
			ImGui::Button("Visuals - Drawing", ImVec2(784, 25));
			ImGui::BeginChild("linke seite", ImVec2(390, 384), true);
			{
				ImGui::Button("Others", ImVec2(372, 25));

				ImGui::Columns(2, nullptr, false);
				ImGui::SetColumnOffset(1, 200);

				ImGui::Checkbox(XorStr("Crosshair Enabled"), &Vars.Visuals.CrosshairOn);
				ImGui::Checkbox(XorStr("Show Spread"), &Vars.Visuals.CrosshairSpread);
				ImGui::Checkbox(XorStr("Show FOV"), &Vars.Visuals.CrosshairFOV);
				ImGui::Checkbox(XorStr("Show Recoil"), &Vars.Visuals.CrosshairType);
				ImGui::Checkbox(XorStr("Rainbow Color"), &Vars.Visuals.CrosshairRainbow);
				ImGui::Text(XorStr("Crosshair Style"));
				ImGui::Combo(XorStr("##CRSHRStyle"), &Vars.Visuals.CrosshairStyle, XorStr("Plus\0\rCircle\0\rBox\0\0"), -1);
				ImGui::Checkbox(XorStr("SpectatorList"), &Vars.Visuals.SpectatorList);



			}ImGui::EndChild();

			ImGui::SameLine();

			ImGui::BeginChild("rechte seite", ImVec2(390, 384), true);
			{
				ImGui::Button("Radar", ImVec2(372, 25));
				ImGui::Checkbox(XorStr("Enable Radar"), &Vars.Visuals.Radar.Enabled);
				ImGui::Text(XorStr("Range"));
				ImGui::SameLine();
				ImGui::SliderInt(XorStr("Range"), &Vars.Visuals.Radar.range, 1, 5);
				ImGui::Checkbox(XorStr("Only Enemy"), &Vars.Visuals.Radar.EnemyOnly);
				ImGui::Checkbox(XorStr("Show Nicknames"), &Vars.Visuals.Radar.Nicks);
			}ImGui::EndChild();
			break;
		}
		case 3:
		{
			ImGui::Button("Visuals - Colors", ImVec2(784, 25));
			ImGui::BeginChild("linke seite", ImVec2(390, 384), true);
			{
				ImGui::Button("Colors", ImVec2(372, 25));
				if (ImGui::ColorEdit3(XorStr("Chams Visible T"), Vars.g_iChamsTV) ||
					ImGui::ColorEdit3(XorStr("Chams Hidden CT"), Vars.g_iChamsCTH) ||
					ImGui::ColorEdit3(XorStr("Chams Hidden T"), Vars.g_iChamsTH) ||
					ImGui::ColorEdit3(XorStr("Chams Visible CT"), Vars.g_iChamsCTV)) color();

			}ImGui::EndChild();
			break;
		}
		}
	}

	void MiscTab()
	{
		switch (Vars.Menu.iMiscSubTab)
		{
		case 0:
		{
			ImGui::Button("Miscellaneous", ImVec2(784, 25));
			ImGui::BeginChild("linke seite", ImVec2(390, 384), true);

			{
				ImGui::Button("Movement and More", ImVec2(372, 25));

				ImGui::Columns(2, nullptr, false);
				ImGui::SetColumnOffset(1, 200);
				ImGui::Checkbox(XorStr("Bunny Hop"), &Vars.Misc.Bhop);
				ImGui::SameLine();
				ImGui::Combo(XorStr("##STRAFER"), &Vars.Misc.AutoStrafe, XorStr("Off\0\rStrafe Helper\0\rFull Strafer\0\0"), -1);
				ImGui::Checkbox(XorStr("Ranks Reveal"), &Vars.Misc.Ranks);
				ImGui::Checkbox(XorStr("Auto Accept"), &Vars.Misc.AutoAccept);
			}ImGui::EndChild();

			ImGui::SameLine();

			ImGui::BeginChild("rechte seite", ImVec2(390, 384), true);
			{
				ImGui::Button("Rage", ImVec2(372, 25));
				ImGui::Combo(XorStr("FakeLag"), &Vars.Misc.FakeLag, XorStr("Off\0\rFactor\0\rSwitch\0\rAdaptive\0\rAdaptive 2\0\0"), -1);
				ImGui::SliderInt(XorStr("##FAKELAG"), &Vars.Misc.FakeLags, 0, 16);
				ImGui::Checkbox(XorStr("Air Stuck"), &Vars.Misc.AirStuck);
				if (Vars.Misc.AirStuck)
				{
					ImGui::SameLine();
					ImGui::Combo(XorStr("Key"), &Vars.Misc.AirStuckKey, keyNames, IM_ARRAYSIZE(keyNames));
				}

			}ImGui::EndChild();
			break;
		}
		case 1:
		{
			ImGui::Button("Spammers", ImVec2(784, 25));
			ImGui::BeginChild("linke seite", ImVec2(390, 384), true);
			{
				ImGui::Button("Spam", ImVec2(372, 25));

				ImGui::Columns(2, nullptr, false);
				ImGui::SetColumnOffset(1, 200);
				ImGui::Text(XorStr("Chat Spam"));
				ImGui::Text(XorStr("Message"));
				ImGui::SameLine();
				ImGui::InputText(XorStr("##SpamMessage"), Vars.Misc.ChatSpamMode, 128);
				ImGui::Text(XorStr("Delay"));
				ImGui::SameLine();
				ImGui::SliderFloat(XorStr("##Spam Delay"), &Vars.Misc.ChatSpamDelay, 0.1f, 10.f);
				ImGui::Checkbox(XorStr("ChatSpam"), &Vars.Misc.ChatSpam);
				ImGui::Checkbox(XorStr("Location Spam"), &Vars.Misc.LocSpam);
				ImGui::Checkbox(XorStr("Enemies only"), &Vars.Misc.LocSpamEnemies);
				ImGui::Checkbox(XorStr("Team Chat"), &Vars.Misc.LocSpamChat);
			}ImGui::EndChild();

			ImGui::SameLine();

			ImGui::BeginChild("rechte seite", ImVec2(390, 384), true);
			{
				ImGui::Button("ClanTags", ImVec2(372, 25));
				ImGui::Text(XorStr("Clantag"));
				//ImGui::Separator();
				ImGui::Checkbox(XorStr("Enabled"), &Vars.Misc.ClantagChanger.enabled);
				ImGui::Text(XorStr("Text"));
				static bool init_clan = false;
				if (!init_clan)
				{
					sprintf(Vars.Misc.ClantagChanger.value, "WRS");
					init_clan = true;
				}

				if (ImGui::InputText(XorStr("##CLANTAGTEXT"), Vars.Misc.ClantagChanger.value, 30))
					E::ClantagChanger->UpdateClanTagCallback();
				ImGui::Text(XorStr("Animation Type"));
				if (ImGui::Combo(XorStr("##ANIM"), &Vars.Misc.ClantagChanger.type, XorStr("Static\0\rMarquee\0\rWords\0\rLetters\0\rTime\0\0"), -1))
					E::ClantagChanger->UpdateClanTagCallback();
				ImGui::Text(XorStr("Animation Speed"));
				if (ImGui::SliderInt(XorStr("##ANIMSPEED"), &Vars.Misc.ClantagChanger.animation_speed, 0, 2000))
					E::ClantagChanger->UpdateClanTagCallback();


			}ImGui::EndChild();
			break;
		}
		case 2:
		{
			ImGui::Button("Configs", ImVec2(784, 25));
			ImGui::BeginChild("linke seite", ImVec2(390, 384), true);
			{
				ImGui::Button("Others", ImVec2(372, 25));

				//ImGui::Text(XorStr("Configs"));
				//ImGui::Separator();
				GetConfigMassive();
				ImGui::Text(XorStr("Config Name"));
				//configs
				static int selectedcfg = 0;
				static std::string cfgname = "default";
				if (ImGui::Combo(XorStr("Parsed Cfgs"), &selectedcfg, [](void* data, int idx, const char** out_text)
				{
					*out_text = configs[idx].c_str();
					return true;
				}, nullptr, configs.size(), 10))
				{
					cfgname = configs[selectedcfg];
					cfgname.erase(cfgname.length() - 4, 4);
					strcpy(Vars.Misc.configname, cfgname.c_str());
				}
				ImGui::InputText(XorStr("Current Cfg"), Vars.Misc.configname, 128);
				if (ImGui::Button(XorStr("Save Config"), ImVec2(93.f, 20.f))) Config->Save();
				ImGui::SameLine();
				if (ImGui::Button(XorStr("Load Config"), ImVec2(93.f, 20.f))) {
					Config->Load(); color();
				}
			}



		}ImGui::EndChild();
		}
	}
}





void Render()
{
	ImGui::GetIO().MouseDrawCursor = Vars.Menu.Opened;

	ImColor mainColor = ImColor(int(15), int(135), int(105), 255);
	ImColor bodyColor = ImColor(int(24), int(24), int(24), 255);
	ImColor fontColor = ImColor(int(255), int(255), int(255), 255);

	ImVec4 mainColorHovered = ImVec4(mainColor.Value.x + 0.1f, mainColor.Value.y + 0.1f, mainColor.Value.z + 0.1f, mainColor.Value.w);
	ImVec4 mainColorActive = ImVec4(mainColor.Value.x + 0.2f, mainColor.Value.y + 0.2f, mainColor.Value.z + 0.2f, mainColor.Value.w);
	ImVec4 menubarColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w - 0.8f);
	ImVec4 frameBgColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w + .1f);
	ImVec4 tooltipBgColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w + .05f);

	if (Vars.Menu.Opened)
	{
		Vars.Menu.flAlpha = clip(Vars.Menu.flAlpha + ALPHA_FREQUENCY * I::Globals->frametime, 0.f, 1.f);

		Vars.Menu.flTabPos = clip(Vars.Menu.flTabPos + POS_FREQUENCY * I::Globals->frametime, 0.f, 398.f);

		ImGuiStyle& style = ImGui::GetStyle();
		ImGuiIO& io = ImGui::GetIO();
		int w;
		int h;
		I::Engine->GetScreenSize(w, h);
		style.Alpha = Vars.Menu.flAlpha;

		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Appearing);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1, 0.1f, 1.f);
		ImGui::Begin("##bg", &Vars.Menu.Opened, ImVec2(w, h), .5f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);
		{

		}ImGui::End();

		style.Colors[ImGuiCol_WindowBg] = bodyColor;
		style.Colors[ImGuiCol_Border] = ImColor(200, 200, 200, 220);
		ImGui::SetNextWindowPos(ImVec2(-400 + Vars.Menu.flTabPos, (h / 2) - 225), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(1600, 700));
		ImGui::Begin("WRS Private Cheat", &Vars.Menu.Opened, ImVec2(500, 800), .75f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoTitleBar);
		{
			if ((Vars.Menu.flSubTabsAlpha == 0 && !Vars.Menu.bShowSubTabs) || !Vars.Menu.bSeeSubTabs)
			{
				Vars.Menu.flTabsAlpha = Vars.Menu.bShowSubTabs ? clip(Vars.Menu.flTabsAlpha - ALPHA_FREQ * I::Globals->frametime, 0, 255) : clip(Vars.Menu.flTabsAlpha + ALPHA_FREQ * I::Globals->frametime, 0, 255);
				Vars.Menu.bSeeSubTabs = false;
			}

			if ((Vars.Menu.flTabsAlpha == 0 && Vars.Menu.bShowSubTabs) || Vars.Menu.bSeeSubTabs)
			{
				Vars.Menu.flSubTabsAlpha = Vars.Menu.bShowSubTabs ? clip(Vars.Menu.flSubTabsAlpha + ALPHA_FREQ * I::Globals->frametime, 0, 255) : clip(Vars.Menu.flSubTabsAlpha - ALPHA_FREQ * I::Globals->frametime, 0, 255);
				Vars.Menu.bSeeSubTabs = true;
			}

			if (!Vars.Menu.bSeeSubTabs)
			{
				style.Colors[ImGuiCol_Border] = ImColor(12, 12, 12, 60);
				if (Vars.Menu.iTab == 0) style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, Vars.Menu.flTabsAlpha); else style.Colors[ImGuiCol_Text] = ImColor(130, 130, 130, Vars.Menu.flTabsAlpha);
				if (ImGui::Button("RAGEBOT", ImVec2(184, 30))) {
					Vars.Menu.iTab = 0; Vars.Menu.bShowSubTabs = true;
				}

				if (Vars.Menu.iTab == 1) style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, Vars.Menu.flTabsAlpha); else style.Colors[ImGuiCol_Text] = ImColor(130, 130, 130, Vars.Menu.flTabsAlpha);
				if (ImGui::Button("LEGIT", ImVec2(184, 30))) {
					Vars.Menu.iTab = 1; Vars.Menu.bShowSubTabs = true;
				}

				if (Vars.Menu.iTab == 2) style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, Vars.Menu.flTabsAlpha); else style.Colors[ImGuiCol_Text] = ImColor(130, 130, 130, Vars.Menu.flTabsAlpha);
				if (ImGui::Button("VISUALS", ImVec2(184, 30))) {
					Vars.Menu.iTab = 2; Vars.Menu.bShowSubTabs = true;
				}

				if (Vars.Menu.iTab == 3) style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, Vars.Menu.flTabsAlpha); else style.Colors[ImGuiCol_Text] = ImColor(130, 130, 130, Vars.Menu.flTabsAlpha);
				if (ImGui::Button("MISC", ImVec2(184, 30))) {
					Vars.Menu.iTab = 3; Vars.Menu.bShowSubTabs = true;
				}
			}
			else
			{
				style.Colors[ImGuiCol_Border] = ImColor(12, 12, 12, 60);
				style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, Vars.Menu.flSubTabsAlpha);
				if (ImGui::Button("< BACK")) Vars.Menu.bShowSubTabs = false;
				ImGui::SameLine();
				switch (Vars.Menu.iTab)
				{
				case 0:
				{
					ImGui::Button("- RAGEBOT");

					if (Vars.Menu.iRageSubTab == 0) style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, Vars.Menu.flSubTabsAlpha); else style.Colors[ImGuiCol_Text] = ImColor(130, 130, 130, Vars.Menu.flSubTabsAlpha);
					if (ImGui::Button("> MAIN", ImVec2(184, 30)))
						Vars.Menu.iRageSubTab = 0;
					if (Vars.Menu.iRageSubTab == 1) style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, Vars.Menu.flSubTabsAlpha); else style.Colors[ImGuiCol_Text] = ImColor(130, 130, 130, Vars.Menu.flSubTabsAlpha);
					if (ImGui::Button("> HVH", ImVec2(184, 30)))
						Vars.Menu.iRageSubTab = 1;
					if (Vars.Menu.iRageSubTab == 2) style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, Vars.Menu.flSubTabsAlpha); else style.Colors[ImGuiCol_Text] = ImColor(130, 130, 130, Vars.Menu.flSubTabsAlpha);
					if (ImGui::Button("> ANTIAIM", ImVec2(184, 30)))
						Vars.Menu.iRageSubTab = 2;
					break;
				}
				case 1:
				{
					ImGui::Button("- LEGITBOT");

					if (Vars.Menu.iLegitSubTab == 0) style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, Vars.Menu.flSubTabsAlpha); else style.Colors[ImGuiCol_Text] = ImColor(130, 130, 130, Vars.Menu.flSubTabsAlpha);
					if (ImGui::Button("> AIMBOT", ImVec2(184, 30)))
						Vars.Menu.iLegitSubTab = 0;
					if (Vars.Menu.iLegitSubTab == 1) style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, Vars.Menu.flSubTabsAlpha); else style.Colors[ImGuiCol_Text] = ImColor(130, 130, 130, Vars.Menu.flSubTabsAlpha);
					if (ImGui::Button("> TRIGGERBOT", ImVec2(184, 30)))
						Vars.Menu.iLegitSubTab = 1;
					break;
				}
				case 2:
				{
					ImGui::Button("- VISUALS");

					if (Vars.Menu.iVisualsSubTab == 0) style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, Vars.Menu.flSubTabsAlpha); else style.Colors[ImGuiCol_Text] = ImColor(130, 130, 130, Vars.Menu.flSubTabsAlpha);
					if (ImGui::Button("> ESP", ImVec2(184, 30)))
						Vars.Menu.iVisualsSubTab = 0;
					if (Vars.Menu.iVisualsSubTab == 1) style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, Vars.Menu.flSubTabsAlpha); else style.Colors[ImGuiCol_Text] = ImColor(130, 130, 130, Vars.Menu.flSubTabsAlpha);
					if (ImGui::Button("> RENDERING", ImVec2(184, 30)))
						Vars.Menu.iVisualsSubTab = 1;
					if (Vars.Menu.iVisualsSubTab == 2) style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, Vars.Menu.flSubTabsAlpha); else style.Colors[ImGuiCol_Text] = ImColor(130, 130, 130, Vars.Menu.flSubTabsAlpha);
					if (ImGui::Button("> OTHERS", ImVec2(184, 30)))
						Vars.Menu.iVisualsSubTab = 2;
					if (Vars.Menu.iVisualsSubTab == 3) style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, Vars.Menu.flSubTabsAlpha); else style.Colors[ImGuiCol_Text] = ImColor(130, 130, 130, Vars.Menu.flSubTabsAlpha);
					if (ImGui::Button("> COLORS", ImVec2(184, 30)))
						Vars.Menu.iVisualsSubTab = 3;
					break;
				}
				case 3:
				{
					ImGui::Button("- MISC");

					if (Vars.Menu.iMiscSubTab == 0) style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, Vars.Menu.flSubTabsAlpha); else style.Colors[ImGuiCol_Text] = ImColor(130, 130, 130, Vars.Menu.flSubTabsAlpha);
					if (ImGui::Button("> Movement", ImVec2(184, 30)))
						Vars.Menu.iMiscSubTab = 0;
					if (Vars.Menu.iMiscSubTab == 1) style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, Vars.Menu.flSubTabsAlpha); else style.Colors[ImGuiCol_Text] = ImColor(130, 130, 130, Vars.Menu.flSubTabsAlpha);
					if (ImGui::Button("> Spammers", ImVec2(184, 30)))
						Vars.Menu.iMiscSubTab = 1;
					if (Vars.Menu.iMiscSubTab == 2) style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, Vars.Menu.flSubTabsAlpha); else style.Colors[ImGuiCol_Text] = ImColor(130, 130, 130, Vars.Menu.flSubTabsAlpha);
					if (ImGui::Button("> Configs", ImVec2(184, 30)))
						Vars.Menu.iMiscSubTab = 2;
				}
				}
			}
		}ImGui::End();

		style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
		style.Colors[ImGuiCol_Border] = ImColor(200, 200, 200, 220);
		ImGui::SetNextWindowPosCenter(ImGuiCond_Appearing);
		ImGui::SetNextWindowSize(ImVec2(800, 450));
		ImGui::SetNextWindowPos(ImVec2((w / 2) - 300, (h / 2) - 225), ImGuiCond_Appearing);
		ImGui::Begin("WRS Private Cheat", &Vars.Menu.Opened, ImVec2(800, 450), .75f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders);
		{
			switch (Vars.Menu.iTab)
			{
			case 0:
				Tabs::RageTab();
				break;
			case 1:
				Tabs::LegitTab();
				break;
			case 2:
				Tabs::VisualsTab();
				break;
			case 3:
				Tabs::MiscTab();
			}
		}ImGui::End();


	}
	else
	{
		Vars.Menu.flAlpha = 0.f;
		Vars.Menu.flTabPos = 0.f;
	}
}

EndSceneFn oEndScene;
long __stdcall Hooks::EndScene(IDirect3DDevice9* pDevice)
{
	if (!G::d3dinit)
		GUI_Init(pDevice);

	H::D3D9->ReHook();

	ImGui::GetIO().MouseDrawCursor = Vars.Menu.Opened;

	ImGui_ImplDX9_NewFrame();

	if (Vars.Visuals.SpectatorList)
		E::Visuals->SpecList();

	Render();

	ImGui::Render();
	return oEndScene(pDevice);
}

ResetFn oReset;
long __stdcall Hooks::Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	if (!G::d3dinit)
		return oReset(pDevice, pPresentationParameters);

	ImGui_ImplDX9_InvalidateDeviceObjects();

	auto hr = oReset(pDevice, pPresentationParameters);
	ImGui_ImplDX9_CreateDeviceObjects();


	return hr;
}

void GUI_Init(IDirect3DDevice9* pDevice)
{
	ImGui_ImplDX9_Init(G::Window, pDevice);

	color();

	G::d3dinit = true;
}
