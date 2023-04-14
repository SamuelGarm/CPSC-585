#include "core/ecs.h"

#include "components.h"

#include <sstream>
#include <string>


ImGuiWindowFlags lfWindowFlags =
  ImGuiWindowFlags_NoBringToFrontOnFocus |
  ImGuiWindowFlags_NoMove |				// text "window" should not move
  // ImGuiWindowFlags_NoResize |				// should not resize
  ImGuiWindowFlags_NoCollapse |			// should not collapse
  ImGuiWindowFlags_NoSavedSettings |		// don't want saved settings mucking things up
  // ImGuiWindowFlags_AlwaysAutoResize |		// window should auto-resize to fit the text
  // ImGuiWindowFlags_NoBackground |			// window should be transparent; only the text should be visible
  ImGuiWindowFlags_NoDecoration |			// no decoration; only the text should be visible
  ImGuiWindowFlags_NoScrollbar |
  ImGuiWindowFlags_NoTitleBar;			// no title; only the text should be visible


ImGuiWindowFlags emptyBackground =
  ImGuiWindowFlags_NoBringToFrontOnFocus |
  ImGuiWindowFlags_NoMove |				// text "window" should not move
  // ImGuiWindowFlags_NoResize |				// should not resize
  ImGuiWindowFlags_NoCollapse |			// should not collapse
  ImGuiWindowFlags_NoSavedSettings |		// don't want saved settings mucking things up
  // ImGuiWindowFlags_AlwaysAutoResize |		// window should auto-resize to fit the text
  ImGuiWindowFlags_NoBackground |			// window should be transparent; only the text should be visible
  ImGuiWindowFlags_NoDecoration |			// no decoration; only the text should be visible
  ImGuiWindowFlags_NoScrollbar |
  ImGuiWindowFlags_NoTitleBar;			// no title; only the text should be visible


ImVec4 colorCodeToImguiVec(std::string colorCode, float opacity);
float hexToFloatByte(std::string h);



void loadFont(std::string fontname,  std::string simplename, float size, ImGuiIO& io, std::unordered_map<std::string,ImFont*>& fonts)
{
  ImFont* font = io.Fonts->AddFontFromFileTTF(fontname.c_str(), size);
  IM_ASSERT(font != NULL);
  fonts[simplename] = font;
}

void LondonFog::loadFonts()
{
  ImGuiIO& io = ImGui::GetIO(); (void)io;

  //load fonts into ImGui
  loadFont("fonts/JockeyOne.ttf", "JockeyOne", 50.f, io, m_fonts);
  loadFont("fonts/JockeyOne.ttf", "JockeyOneLarge", 130.f, io, m_fonts);


}





void LondonFog::setStyle()
{
  
  ImGuiStyle& style = ImGui::GetStyle();
  
  // light style from Pacôme Danhiez (user itamago) https://github.com/ocornut/imgui/pull/511#issuecomment-175719267
  // style.Alpha = 1.0f;
  // style.FrameRounding = 3.0f;
  // style.Colors[ImGuiCol_Text]                  = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  // style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
  // style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.94f, 0.94f, 0.94f, 0.94f);
  // // style.Colors[ImGuiCol_ChildWindowBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  // style.Colors[ImGuiCol_PopupBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
  // style.Colors[ImGuiCol_Border]                = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
  // style.Colors[ImGuiCol_BorderShadow]          = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
  // style.Colors[ImGuiCol_FrameBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
  // style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
  // style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  // style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
  // style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
  // style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
  // style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
  // style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
  // style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
  // style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
  // style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
  // // style.Colors[ImGuiCol_ComboBg]               = ImVec4(0.86f, 0.86f, 0.86f, 0.99f);
  // style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  // style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
  // style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  // style.Colors[ImGuiCol_Button]                = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
  // style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  // style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
  // style.Colors[ImGuiCol_Header]                = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
  // style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
  // style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  // // style.Colors[ImGuiCol_Column]                = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
  // // style.Colors[ImGuiCol_ColumnHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
  // // style.Colors[ImGuiCol_ColumnActive]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  // style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
  // style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  // style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
  // // style.Colors[ImGuiCol_CloseButton]           = ImVec4(0.59f, 0.59f, 0.59f, 0.50f);
  // // style.Colors[ImGuiCol_CloseButtonHovered]    = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
  // // style.Colors[ImGuiCol_CloseButtonActive]     = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
  // style.Colors[ImGuiCol_PlotLines]             = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
  // style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  // style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  // style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
  // style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
  // // style.Colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

  // if( bStyleDark_ )
  // {
  //     for (int i = 0; i <= ImGuiCol_COUNT; i++)
  //     {
  //         ImVec4& col = style.Colors[i];
  //         float H, S, V;
  //         ImGui::ColorConvertRGBtoHSV( col.x, col.y, col.z, H, S, V );

  //         if( S < 0.1f )
  //         {
  //             V = 1.0f - V;
  //         }
  //         ImGui::ColorConvertHSVtoRGB( H, S, V, col.x, col.y, col.z );
  //         if( col.w < 1.00f )
  //         {
  //             col.w *= alpha_;
  //         }
  //     }
  // }
  // else
  // {
  //     for (int i = 0; i <= ImGuiCol_COUNT; i++)
  //     {
  //         ImVec4& col = style.Colors[i];
  //         if( col.w < 1.00f )
  //         {
  //             col.x *= alpha_;
  //             col.y *= alpha_;
  //             col.z *= alpha_;
  //             col.w *= alpha_;
  //         }
  //     }
  // }


}


std::string getRankSuffix(int rank)
{
  int ending = rank % 10;
  switch (ending)
  {
    case 1:
      return "st";
    case 2:
      return "nd";
    case 3:
      return "rd";
    default:
      return "th";
  } 

}

void LondonFog::drawHUD(Guid carGuid, ecs::Scene scene, BoundingBox region, RaceTracker& raceSystem)
{

  // get the associated data  

  // start the imgui calls

  // setup the style


  // start with current speed
  // lower left corner.

  Car& car = scene.GetComponent<Car>(carGuid);



  // wrong way prompt

  if (car.isWrongWay())
  {


    ImGui::SetNextWindowSize(ImVec2(0.f,0.f));
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::Begin("warning", false, emptyBackground);

    m_texts["wrongway"].Render();



    ImGui::End();
  }


  // hud 

  float startY{0.73f};
  float startX{0.015f};

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{18.f, 12.f});
  ImGui::PushStyleColor(ImGuiCol_WindowBg, colorCodeToImguiVec("#EF1A1A", 0.65f));
  ImGui::PushFont(m_fonts["JockeyOne"]);

  std::string label_hud = std::string("hud_") + std::to_string(carGuid);

  ImGui::SetNextWindowSize(ImVec2(0.f,0.f));
  ImGui::SetNextWindowPos(ImVec2(region.x + startX * region.w, region.y + startY * region.h));
  std::string label_speed = std::string("speed_") + std::to_string(carGuid);

  ImGui::Begin(label_speed.c_str(),false,lfWindowFlags);

  ImGui::SetWindowFontScale(1.f);

  auto carSpeed = car.carSpeed();

  ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Current Speed");
  ImGui::PushFont(m_fonts["JockeyOneLarge"]);
  ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "%.0f", clamp((carSpeed * (carSpeed / 10.f)), 0.f, 500.f));
  ImGui::PopFont();
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "cm/s");

  ImGui::End();




  float itemWidth{0.10f};
  float startOff{0.7f};
  float gap{15.f};

  // then do the rank
  ImGui::SetNextWindowSize(ImVec2(0.f,0.f));
  // ImGui::SetNextWindowPos(ImVec2((region.x + region.w) - (region.w * startX), region.y + startY * region.h));
  std::string label_rank = std::string("rank_") + std::to_string(carGuid);
  
  ImGui::Begin(label_rank.c_str(),false,lfWindowFlags);
  ImVec2 v = ImGui::GetWindowSize();
  ImGui::SetWindowPos(ImVec2((region.x + region.w) - (region.w * startX) - v.x, region.y + startY * region.h));


  int ranking = raceSystem.getRanking(carGuid);
  ImGui::BeginGroup();
  ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Rank");
  ImGui::PushFont(m_fonts["JockeyOneLarge"]);
  ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "%d", ranking);
  ImGui::PopFont();
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), getRankSuffix(ranking).c_str());
  ImGui::EndGroup();

  for (int i =0; i < 9; i++)
  {
    ImGui::SameLine();
    ImGui::Spacing();
  }

  ImGui::SameLine();

  ImGui::BeginGroup();  
  ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Lap");
  ImGui::PushFont(m_fonts["JockeyOneLarge"]);
  ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "%d/%d", raceSystem.getLapCount(carGuid), raceSystem.MAX_LAPS);
  ImGui::PopFont();
  ImGui::EndGroup();

  ImGui::End();

  // next, do the lapcount
  // ImGui::SetNextWindowSize(ImVec2(region.w * itemWidth,0.f));
  // ImGui::SetNextWindowPos(ImVec2(region.x + startOff * region.w + (region.w * itemWidth) + gap, region.y + startY * region.h));
  // std::string label_lap = std::string("lapcount_") + std::to_string(carGuid);
  
  // ImGui::Begin(label_lap.c_str(),false,lfWindowFlags);


  // ImGui::End();


  ImGui::PopFont();
  ImGui::PopStyleColor();
  ImGui::PopStyleVar();
  



  // pop the style



}




void LondonFog::drawMenu(int width, int height)
{
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{18.f, 12.f});
  ImGui::PushStyleColor(ImGuiCol_WindowBg, colorCodeToImguiVec("#EF1A1A", 0.65f));
  ImGui::PushFont(m_fonts["JockeyOne"]);

  if (m_status == MAIN_SCREEN)
  {

    ImGui::SetNextWindowSize(ImVec2(0.f,0.f));



    ImGui::Begin("mainmenu");

    ImVec2 v = ImGui::GetWindowSize();

    // should take up right side of screen
    // all in one window? or should I split it up??
    ImGui::SetWindowPos(ImVec2());


    // ImGui::Button("ACTION", ImVec2((size.x - ImGui::GetStyle().ItemSpacing.x) * 0.5f, size.y));
    // ImGui::Button("ACTION", ImVec2((size.x - ImGui::GetStyle().ItemSpacing.x) * 0.5f, size.y));
    // ImGui::Button("ACTION", ImVec2((size.x - ImGui::GetStyle().ItemSpacing.x) * 0.5f, size.y));

    

    ImGui::End();
  }





  
}


ImVec4 colorCodeToImguiVec(std::string colorCode, float opacity)
{

  // #abcdef
  // 0123456

  // Function to parse HTML color code and return RGBA vector

  auto red_str    = colorCode.substr(1,2);
  auto green_str  = colorCode.substr(3,2);
  auto blue_str   = colorCode.substr(5,2);

  // color - 65

  // Extract red, green, blue values from integer
  float red   = hexToFloatByte(red_str);
  float green = hexToFloatByte(green_str);
  float blue  = hexToFloatByte(blue_str);

  // Add values to vector and return

  return ImVec4(red, green, blue, opacity);
}


float hexToFloatByte(std::string h)
{
  unsigned int rgb;
  std::stringstream ss;
  ss << std::hex << h;
  ss >> rgb;
  return static_cast<float>(rgb) / 255.0f;
}



// Simple helper function to load an image into a OpenGL texture with common settings
bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

void LondonFog::loadTextures()
{
  UITexture wrongWay{"textures/wrongway.png"};
  m_texts["wrongway"] = wrongWay;

}
