#define SDL_MAIN_HANDLED
#include "SDL2/include/SDL.h"
#include "SDL2/include/SDL_image.h"
#include "SDL2/include/SDL_mixer.h"
#include "SDL2/include/SDL_ttf.h"
#include <string>
#include <cmath>
#include <iomanip>
#include <iostream>

struct TextObject {
    SDL_Texture* texture;
    SDL_Rect rect;
};

TextObject CreateText(SDL_Renderer* renderer, TTF_Font* font,
                      const std::string& text, SDL_Color color,
                      int x, int y)
{
    TextObject obj{};
    SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!surf) {
        SDL_Log("❌ TTF_RenderText_Blended error: %s", TTF_GetError());
        return obj;
    }

    obj.texture = SDL_CreateTextureFromSurface(renderer, surf);
    if (!obj.texture) {
        SDL_Log("❌ SDL_CreateTextureFromSurface error: %s", SDL_GetError());
        SDL_FreeSurface(surf);
        return obj;
    }

    SDL_QueryTexture(obj.texture, NULL, NULL, &obj.rect.w, &obj.rect.h);
    obj.rect.x = x;
    obj.rect.y = y;

    SDL_FreeSurface(surf);
    return obj;
}

int sdl_quit() {
	SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* image = nullptr;
    SDL_Texture* textTexture = nullptr;
    TTF_Font* font = nullptr;
    SDL_Surface* surface = nullptr;
    Mix_Chunk* buttonSound = nullptr;
	
	SDL_StopTextInput();
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(textTexture);
	TTF_CloseFont(font);
	SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeChunk(buttonSound);
	Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
    std::cout << "👋 Closing projectILE. Have a good day!\n";
    return 0;
}

int main(int argc, char* argv[]) {
	std::cout << "⚙️ projectILE by Sceawere @2025\n";
	//SDL INIT
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "❌ SDL2 Can't initialize the audio, please contact developers.\n";
        std::cerr << "❌ SDL_INIT_AUDIO_ERROR : " << Mix_GetError() << "\n";
        return 1;
    }
    
    std::cout << "✅ All modules initialized successfully.\n";
	
	//ERROR HANDLING
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "❌ SDL2 Can't initialize the video, please contact developers.\n";
        std::cerr << "❌ SDL_INIT_VIDEO_ERROR : " << SDL_GetError() << "\n";
        return 1;
    }
   
	//WINDOW
    SDL_Window* window = SDL_CreateWindow(
        "projectILE PUBLIC",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1000, 1000,
        SDL_WINDOW_SHOWN
    );
    std::cout << "✅ The window created successfully.\n";
    
    if (!window) {
		std::cout << "❌ SDL2 Can't create the window, please contact developers.\n";
        std::cerr << "❌ SDL_WINDOW_ERROR: " << SDL_GetError() << "\n";
        return 1;
    }
    
	//WINDOW RENDER
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    //SOUND LOAD
    Mix_Chunk* buttonSound = Mix_LoadWAV("button.wav");
	if (!buttonSound) {
		std::cout << "❌ SDL2 Can't load the sound file\n";
		std::cout << "⁉️ Did you delete or change the name of 'button.wav' file?\n";
		std::cerr << "❌ SDL_SOUND_LOAD_ERROR: " <<	Mix_GetError() << "\n";
		return 1;
	}

    //FONT LOAD
	TTF_Font* font = TTF_OpenFont("unageo.ttf", 25);
	if (!font) {
		std::cout << "❌ SDL2 Can't load the font\n";
		std::cout << "⁉️ Did you delete or change the name of 'unageo.ttf' file?\n";
		std::cerr << "❌ SDL_FONT_LOAD_ERROR: " <<	TTF_GetError() << "\n";
		return 1;
	}
	std::cout << "✅ Font loaded successfully.\n";
	
	SDL_Texture* ILE_logo = IMG_LoadTexture(renderer, "textures/projectile_logo.png");
    SDL_Texture* change_e_variable_button = IMG_LoadTexture(renderer, "textures/change_e_variable_button.png");
    SDL_Texture* exit_button = IMG_LoadTexture(renderer, "textures/exit_button.png");
    SDL_Texture* launch_angle_calc_button = IMG_LoadTexture(renderer, "textures/launch_angle_calc_button.png");
    SDL_Texture* ashot_arrow = IMG_LoadTexture(renderer, "textures/ashot_arrow.png");
    
    //CALCULATOR IMAGES
    SDL_Texture* main_menu = IMG_LoadTexture(renderer, "textures/main_menu.png");
    SDL_Texture* enter_button = IMG_LoadTexture(renderer, "textures/enter.png");
    SDL_Texture* warning = IMG_LoadTexture(renderer, "textures/warning.png");
    SDL_Texture* warning1 = IMG_LoadTexture(renderer, "textures/warning1.png");
    SDL_Texture* calculatee = IMG_LoadTexture(renderer, "textures/calculate.png");
    SDL_Texture* ew = IMG_LoadTexture(renderer, "textures/ew.png");
    SDL_Texture* et = IMG_LoadTexture(renderer, "textures/et.png");
    SDL_Texture* emv = IMG_LoadTexture(renderer, "textures/emv.png");
    SDL_Texture* ehfta = IMG_LoadTexture(renderer, "textures/ehfta.png");
    SDL_Texture* e_launch_angle = IMG_LoadTexture(renderer, "textures/enter_l_angle.png");
    SDL_Texture* c_air_pressure = IMG_LoadTexture(renderer, "textures/c_air_pressure.png");
    SDL_Texture* c_error_tolerance = IMG_LoadTexture(renderer, "textures/c_error_tolerance.png");
    SDL_Texture* c_gravity = IMG_LoadTexture(renderer, "textures/c_gravity.png");
    SDL_Texture* c_gas_constant = IMG_LoadTexture(renderer, "textures/c_gas_constant.png");
    SDL_Surface* iconSurface = IMG_Load("projectILE_icon.png");
    SDL_SetWindowIcon(window, iconSurface);
    SDL_FreeSurface(iconSurface);
    
    //image size
    int Wlogo, Wwarning, W250, W200, W100;
    int Hlogo, Hwarning, H150, H100;
    
	SDL_QueryTexture(change_e_variable_button, nullptr, nullptr, &W250, &H150);
	SDL_QueryTexture(main_menu, nullptr, nullptr, &W100, &H100);
	SDL_QueryTexture(ew, nullptr, nullptr, &W200, &H100);
	SDL_QueryTexture(warning, nullptr, nullptr, &Wwarning, &Hwarning);
	SDL_QueryTexture(warning1, nullptr, nullptr, &Wwarning, &Hwarning);
	SDL_QueryTexture(ILE_logo, nullptr, nullptr, &Wlogo, &Hlogo);
	
	//image rect
	SDL_Rect menu_button_1_rect = {550, 350, W250, H150};
	SDL_Rect menu_button_2_rect = {200, 350, W250, H150};
	SDL_Rect menu_button_3_rect = {200, 550, W250, H150};
	SDL_Rect menu_button_4_rect = {550, 550, W250, H150};
	SDL_Rect exit_button_rect = {895, 895, W100, H100};
	SDL_Rect buttonRect14 = {360, 725, W100, H100};
	SDL_Rect enter_button_1_rect = {350, 550, W100, H100};
	SDL_Rect calculate_rect = {100, 725, W200, H100};
	SDL_Rect buttonRect10 = {100, 50, W200, H100};
	SDL_Rect buttonRect11 = {100, 175, W200, H100};
	SDL_Rect buttonRect12 = {100, 300, W200, H100};
	SDL_Rect buttonRect13 = {100, 425, W200, H100};
	SDL_Rect buttonRect15 = {465, 725, Wwarning, Hwarning};
	SDL_Rect cairp_button_rect = {100, 50, W200, H100};
	SDL_Rect cerrort_button_rect = {100, 175, W200, H100};
	SDL_Rect cgravity_button_rect = {100, 300, W200, H100};
	SDL_Rect cconstant_button_rect = {100, 425, W200, H100};
	SDL_Rect ILE_logo_rect = {240, 60, Wlogo, Hlogo};
	
	std::cout << "✅ Images loaded/initialized successfully\n";
	
	double air_pressure = 101325;
	const double temp_celcius = 15.0;
	double error_tolerance = 0.5;
	
	//MAIN LOOP VARIABLES
    bool running = true;
    bool typing = false;
    bool calculate = false;
    std::string screens = "MAIN_MENU";
    
    //CALCULATION VARIABLES
    std::string inputText;
    double error_handler = 0.0;
    double best_error_low = 9e9;
	double best_error_high = 9e9;
	double best_angle_low = 0.0;
	double best_angle_high = 0.0;
    double writing_variable = 0.0;
    double velocity = 0.0;
    double target = 0.0;
    double diameter = 0.0;
    double mass = 0.0;
    double launch_angle = 0.0;
    double landing_pos = 0.0;
    double max_height_reach = 0.0;
    double total_time = 0.0;
    double gas_constant = 287.057;
	double gravity = 9.807;
	const double drag_coefficient = 0.0;
    double* current_variable = nullptr;
    SDL_Event event;
    
    std::cout << "✅ Variables created/initialized successfully\n";
    
    //FONT RENDER
	SDL_Color textColor_black = {0, 0, 0};
	
	TextObject menu_text1 = CreateText(renderer, font, "projectILE by Sceawere @2025-Nov-17", textColor_black, 5, 875);
	TextObject menu_text2 = CreateText(renderer, font, "Button click sound: Universfield from Pixabay", textColor_black, 5, 935);
	TextObject menu_text3 = CreateText(renderer, font, "Unageo font: Richard Sepsi", textColor_black, 5, 905);
	TextObject menu_text4 = CreateText(renderer, font, "projectILE public version. do not redistribute it.", textColor_black, 5, 965);
	
	TextObject cng_env_text_1 = CreateText(renderer, font, "You're writing the gravity now... (m/s2)", textColor_black, 72, 870);
	TextObject cng_env_text_2 = CreateText(renderer, font, "You're writing the gas constant now... (J/(kg*K))", textColor_black, 72, 870);
	TextObject cng_env_text_3 = CreateText(renderer, font, "You're writing the error tolerance now... (meters)", textColor_black, 72, 870);
	TextObject cng_env_text_5 = CreateText(renderer, font, "You're writing the air pressure now... (pascals)", textColor_black, 72, 870);
	
	TextObject env_variable_text = CreateText(renderer, font, "= Environment Variables =", textColor_black, 425, 50);
	TextObject calc_results_text = CreateText(renderer, font, "= Calculation Results =", textColor_black, 425, 350);
	TextObject entering_text = CreateText(renderer, font, ">> = ", textColor_black, 72, 900);
	TextObject writing_text_1 = CreateText(renderer, font, "You're writing the muzzle velocity now... (m/s)", textColor_black, 72, 870);
	TextObject writing_text_shot_2 = CreateText(renderer, font, "You're writing the launch angle now... (0-89 degrees)", textColor_black, 72, 870);
	TextObject writing_text_3 = CreateText(renderer, font, "You're writing the diameter now... (milimeter)", textColor_black, 72, 870);
	TextObject writing_text_4 = CreateText(renderer, font, "You're writing the weight now... (kilogram)", textColor_black, 72, 870);
	TextObject writing_text_launch_2 = CreateText(renderer, font, "You're writing how far target away now... (meters)", textColor_black, 72, 870);
    
	std::string prevAirText;
	SDL_Texture* textTexture4 = nullptr;
	SDL_Rect textRect4 = {425, 100, 0, 0};
	
	std::string prevTempText;
	SDL_Texture* textTexture5 = nullptr;
	SDL_Rect textRect5 = {425, 140, 0, 0};
	
	std::string prevErrText;
	SDL_Texture* textTexture6 = nullptr;
	SDL_Rect textRect6 = {425, 180, 0, 0};
	
	std::string prevBalText;
	SDL_Texture* textTexture10 = nullptr;
	SDL_Rect textRect10 = {425, 400, 0, 0};
	
	std::string prevBahText;
	SDL_Texture* textTexture11 = nullptr;
	SDL_Rect textRect11 = {425, 440, 0, 0};
	
	std::string prevLandText;
	SDL_Texture* land_text_texture = nullptr;
	SDL_Rect LandRect = {425, 400, 0, 0};
	
	std::string prevHeighttext;
	SDL_Texture* height_text_texture = nullptr;
	SDL_Rect HeightRect = {425, 440, 0, 0};
	
	std::string prevAirTimeText;
	SDL_Texture* airtime_text_texture = nullptr;
	SDL_Rect AirRect = {425, 480, 0, 0};
	
	std::string prevGravityText;
	SDL_Texture* gravity_text_texture = nullptr;
	SDL_Rect GravityRect = {425, 220, 0, 0};
	
	std::string prevGasConstantText;
	SDL_Texture* gasconstant_text_texture = nullptr;
	SDL_Rect GasConstantRect = {425, 260, 0, 0};
	
	std::cout << "✅ All text created successfully\n";
	
	std::cout << "✅ If you see this message, all modules/images/texts working without problem...\n";
   
	//MAIN LOOP
    while (running) {
		
		std::ostringstream Airstream;
		Airstream << std::fixed << std::setprecision(3) << air_pressure;
		std::string airText = Airstream.str() + " pascals air pressure.";

		if (airText != prevAirText) {
			prevAirText = airText;

			if (textTexture4) {
				SDL_DestroyTexture(textTexture4);
				textTexture4 = nullptr;
			}

			SDL_Surface* textSurface4 = TTF_RenderText_Blended(font, airText.c_str(), textColor_black);
			if (textSurface4) {
				textTexture4 = SDL_CreateTextureFromSurface(renderer, textSurface4);
				SDL_FreeSurface(textSurface4);

				SDL_QueryTexture(textTexture4, NULL, NULL, &textRect4.w, &textRect4.h);
			}
		}
		
		std::ostringstream Tempstream;
		Tempstream << std::fixed << std::setprecision(1) << temp_celcius;
		std::string tempText = Tempstream.str() + " celcius air temperature.";

		if (tempText != prevTempText) {
			prevTempText = tempText;

			if (textTexture5) {
				SDL_DestroyTexture(textTexture5);
				textTexture5 = nullptr;
			}

			SDL_Surface* textSurface5 = TTF_RenderText_Blended(font, tempText.c_str(), textColor_black);
			if (textSurface5) {
				textTexture5 = SDL_CreateTextureFromSurface(renderer, textSurface5);
				SDL_FreeSurface(textSurface5);

				SDL_QueryTexture(textTexture5, NULL, NULL, &textRect5.w, &textRect5.h);
			}
		}
		
		std::ostringstream Errorstream;
		Errorstream << std::fixed << std::setprecision(2) << error_tolerance;
		std::string errText = Errorstream.str() + " meters error tolerance.";

		if (errText != prevErrText) {
			prevErrText = errText;

			if (textTexture6) {
				SDL_DestroyTexture(textTexture6);
				textTexture6 = nullptr;
			}

			SDL_Surface* textSurface6 = TTF_RenderText_Blended(font, errText.c_str(), textColor_black);
			if (textSurface6) {
				textTexture6 = SDL_CreateTextureFromSurface(renderer, textSurface6);
				SDL_FreeSurface(textSurface6);

				SDL_QueryTexture(textTexture6, NULL, NULL, &textRect6.w, &textRect6.h);
			}
		}
		
		std::ostringstream GravityStream;
		GravityStream << std::fixed << std::setprecision(2) << gravity;
		std::string gravityText = GravityStream.str() + " m/s2 gravitational acceleration.";

		if (gravityText != prevGravityText) {
			prevGravityText = gravityText;

			if (gravity_text_texture) {
				SDL_DestroyTexture(gravity_text_texture);
				gravity_text_texture = nullptr;
			}

			SDL_Surface* textSurfacegrav = TTF_RenderText_Blended(font, gravityText.c_str(), textColor_black);
			if (textSurfacegrav) {
				gravity_text_texture = SDL_CreateTextureFromSurface(renderer, textSurfacegrav);
				SDL_FreeSurface(textSurfacegrav);

				SDL_QueryTexture(gravity_text_texture, NULL, NULL, &GravityRect.w, &GravityRect.h);
			}
		}
		
		std::ostringstream GasConstantStream;
		GasConstantStream << std::fixed << std::setprecision(2) << gas_constant;
		std::string gasconstant_text = GasConstantStream.str() + " joules per kilogram per kelvin gas constant.";

		if (gasconstant_text != prevGasConstantText) {
			prevGasConstantText = gasconstant_text;

			if (gasconstant_text_texture) {
				SDL_DestroyTexture(gasconstant_text_texture);
				gasconstant_text_texture = nullptr;
			}

			SDL_Surface* textSurfacegas = TTF_RenderText_Blended(font, gasconstant_text.c_str(), textColor_black);
			if (textSurfacegas) {
				gasconstant_text_texture = SDL_CreateTextureFromSurface(renderer, textSurfacegas);
				SDL_FreeSurface(textSurfacegas);

				SDL_QueryTexture(gasconstant_text_texture, NULL, NULL, &GasConstantRect.w, &GasConstantRect.h);
			}
		}
		
		//SCREENS
		if (screens == "ARROW") {
					
			std::ostringstream Landstream;
			Landstream << std::fixed << std::setprecision(2) << landing_pos;
			std::string LandText = Landstream.str() + " meters away projectile landed.";

			if (LandText != prevLandText) {
				prevLandText = LandText;

				if (land_text_texture) {
					SDL_DestroyTexture(land_text_texture);
					land_text_texture = nullptr;
				}

				
				SDL_Surface* LandSurface = TTF_RenderText_Blended(font, LandText.c_str(), textColor_black);
					if (LandSurface) {
						land_text_texture = SDL_CreateTextureFromSurface(renderer, LandSurface);
						SDL_FreeSurface(LandSurface);

						SDL_QueryTexture(land_text_texture, NULL, NULL, &LandRect.w, &LandRect.h);
				}
			}
			
			std::ostringstream Heightstream;
			Heightstream << std::fixed << std::setprecision(2) << max_height_reach;
			std::string Heighttext = Heightstream.str() + " meters maximum altitude.";

			if (Heighttext != prevHeighttext) {
				prevHeighttext = Heighttext;

				if (height_text_texture) {
					SDL_DestroyTexture(height_text_texture);
					height_text_texture = nullptr;
				}

				
				SDL_Surface* HeightSurf = TTF_RenderText_Blended(font, Heighttext.c_str(), textColor_black);
					if (HeightSurf) {
						height_text_texture = SDL_CreateTextureFromSurface(renderer, HeightSurf);
						SDL_FreeSurface(HeightSurf);

						SDL_QueryTexture(height_text_texture, NULL, NULL, &HeightRect.w, &HeightRect.h);
				}
			}
			
			std::ostringstream AirTimeStream;
			AirTimeStream << std::fixed << std::setprecision(2) << total_time;
			std::string AirTimetext = AirTimeStream.str() + " seconds it spend on air.";

			if (AirTimetext != prevAirTimeText) {
				prevAirTimeText = AirTimetext;

				if (airtime_text_texture) {
					SDL_DestroyTexture(airtime_text_texture);
					airtime_text_texture = nullptr;
				}

				
				SDL_Surface* AirTextSurf = TTF_RenderText_Blended(font, AirTimetext.c_str(), textColor_black);
					if (AirTextSurf) {
						airtime_text_texture = SDL_CreateTextureFromSurface(renderer, AirTextSurf);
						SDL_FreeSurface(AirTextSurf);

						SDL_QueryTexture(airtime_text_texture, NULL, NULL, &AirRect.w, &AirRect.h);
				}
			}
			
			//EVENT HANDLER
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					sdl_quit();
					running = false;
				}
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					SDL_Point mousePoint = { event.button.x, event.button.y };
					if (SDL_PointInRect(&mousePoint, &buttonRect13)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						writing_variable = 1.0;
						current_variable = &velocity;
						typing = true;
						SDL_StartTextInput();
						std::cout << "Enter muzzle velocity of the projectile (m/s)" << std::endl;	
					}
					if (SDL_PointInRect(&mousePoint, &buttonRect12)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						writing_variable = 2.0;
						current_variable = &launch_angle;
						typing = true;
						SDL_StartTextInput();
						std::cout << "Enter launch angle (degrees)" << std::endl;	
					}
					if (SDL_PointInRect(&mousePoint, &buttonRect11)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						writing_variable = 3.0;
						current_variable = &diameter;
						typing = true;
						SDL_StartTextInput();
						std::cout << "Enter diameter of the projectile (mm)" << std::endl;	
					}
					if (SDL_PointInRect(&mousePoint, &buttonRect10)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						writing_variable = 4.0;
						current_variable = &mass;
						typing = true;
						SDL_StartTextInput();
						std::cout << "Enter weight of the projectile (kg)" << std::endl;	
					}
					if (SDL_PointInRect(&mousePoint, &buttonRect14)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						// Done typing
						writing_variable = 0.0;
						typing = false;
						SDL_StopTextInput();
						if (current_variable) {
							*current_variable = std::stod(inputText);
							std::cout << "Saved as: " << *current_variable << std::endl;
						}
						current_variable = nullptr;
						inputText.clear();
					}
					if (SDL_PointInRect(&mousePoint, &calculate_rect)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						calculate = true;
						error_handler = 0.0;

						if (velocity > 0 && launch_angle > 0 && diameter > 0 && mass > 0) {
							if (calculate == true) {
								
								//UNIT ARRANGEMENTS
								double temp_kelvin = temp_celcius + 273.15;
								
								//ENVIRONMENTAL EFFECTS
								double air_density = air_pressure / (gas_constant * temp_kelvin);

							   //PROJECTILE CALCULATION
								const double radius = diameter / 2.0 / 1000.0;
								const double area = M_PI * radius * radius;

								//LAST CALC.
								const double angle_rad = launch_angle * M_PI / 180.0;
								double vx = velocity * std::cos(angle_rad);
								double vy = velocity * std::sin(angle_rad);
								
								double x = 0.0;
								double y = 0.0;

								//TIME (SECONDS)
								const double dt = 0.01;
								
								//END USER INFO.
								double max_height = y;
								total_time = 0.0;

								 //SIM LOOP
								while (y >= 0.0) {
									double speed = std::sqrt(vx * vx + vy * vy);
									double drag_force = 0.5 * air_density * drag_coefficient * area * speed * speed;
									
									if (y > max_height) {
										max_height = y;
									}

									//DRAG EFFECT ON PROJECTILE
									double ax = -drag_force * (vx / speed) / mass;
									double ay = -drag_force * (vy / speed) / mass - gravity;

									//VELOCITY UPDATE
									vx += ax * dt;
									vy += ay * dt;

									//POSITION UPDATE
									x += vx * dt;
									y += vy * dt;
									
									total_time += dt;
									
								}
								
								//END USER INFO
								std::cout << " \n";
								std::cout << "Projectile landed " << x << " meters away from it's launch point.\n";
								std::cout << "Projectile reached maximum altitude of " << max_height << " meters.\n";
								std::cout << "Projectile spend " << total_time << " seconds from launch to landing.\n";
								landing_pos = x;
								max_height_reach = max_height;								
								
							calculate = false;
							}
						} else {
								std::cout << "Please enter all the information needed." << std::endl;
								error_handler = 1.0;
							}
					}
					
					if (SDL_PointInRect(&mousePoint, &exit_button_rect)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						screens = "MAIN_MENU";
						writing_variable = 0.0;
					}
				}
				if (event.type == SDL_TEXTINPUT && typing) {
					inputText += event.text.text;
				}
				if (event.type == SDL_KEYDOWN && typing) {
					if (event.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty()) {
						inputText.pop_back();
					}
					else if (event.key.keysym.sym == SDLK_RETURN) {
						// Done typing
						writing_variable = 0.0;
						typing = false;
						SDL_StopTextInput();
						if (current_variable) {
							*current_variable = std::stod(inputText);
							std::cout << "Saved as: " << *current_variable << std::endl;
						}
						current_variable = nullptr;
						inputText.clear();
					}
				}
			}
		
			
			//renderer start
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);
			
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			
			SDL_RenderCopy(renderer, main_menu, nullptr, &exit_button_rect);
			SDL_RenderCopy(renderer, ew, nullptr, &buttonRect10);
			SDL_RenderCopy(renderer, et, nullptr, &buttonRect11);
			SDL_RenderCopy(renderer, e_launch_angle, nullptr, &buttonRect12);
			SDL_RenderCopy(renderer, emv, nullptr, &buttonRect13);
			SDL_RenderCopy(renderer, calculatee, nullptr, &calculate_rect);
			SDL_RenderCopy(renderer, enter_button, nullptr, &buttonRect14);
			
			if (error_handler == 1.0) {
				SDL_RenderCopy(renderer, warning1, nullptr, &buttonRect15);
			}
			
			
			SDL_RenderCopy(renderer, env_variable_text.texture, NULL, &env_variable_text.rect);
			SDL_RenderCopy(renderer, textTexture4, NULL, &textRect4);
			SDL_RenderCopy(renderer, textTexture5, NULL, &textRect5);
			SDL_RenderCopy(renderer, textTexture6, NULL, &textRect6);
			SDL_RenderCopy(renderer, entering_text.texture, NULL, &entering_text.rect);
			SDL_RenderCopy(renderer, calc_results_text.texture, NULL, &calc_results_text.rect);
			SDL_RenderCopy(renderer, land_text_texture, NULL, &LandRect);
			SDL_RenderCopy(renderer, height_text_texture, NULL, &HeightRect);
			SDL_RenderCopy(renderer, airtime_text_texture, NULL, &AirRect);
			SDL_RenderCopy(renderer, gravity_text_texture, NULL, &GravityRect);
			SDL_RenderCopy(renderer, gasconstant_text_texture, NULL, &GasConstantRect);
			
			if (writing_variable == 1.0) {
				SDL_RenderCopy(renderer, writing_text_1.texture, NULL, &writing_text_1.rect);
			}
			
			if (writing_variable == 2.0) {
				SDL_RenderCopy(renderer, writing_text_shot_2.texture, NULL, &writing_text_shot_2.rect);
			}
			
			if (writing_variable == 3.0) {
				SDL_RenderCopy(renderer, writing_text_3.texture, NULL, &writing_text_3.rect);
			}
			
			if (writing_variable == 4.0) {
				SDL_RenderCopy(renderer, writing_text_4.texture, NULL, &writing_text_4.rect);
			}
			
			if (!inputText.empty()) {
				SDL_Surface* textSurface = TTF_RenderText_Blended(font, inputText.c_str(), textColor_black);
				SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
				SDL_Rect textRect = {130, 900, textSurface->w, textSurface->h};
				SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
				SDL_FreeSurface(textSurface);
				SDL_DestroyTexture(textTexture);
			}
			
			//renderer end
			SDL_RenderPresent(renderer);
			SDL_Delay(50);
		}
		if (screens == "LAUNCH_ANGLE") {
				
			std::ostringstream Balstream;
			Balstream << std::fixed << std::setprecision(5) << best_angle_low;
			std::string balText = Balstream.str() + " Degrees (lower arc, less air time)";

			if (balText != prevBalText) {
				prevBalText = balText;

				if (textTexture10) {
					SDL_DestroyTexture(textTexture10);
					textTexture10 = nullptr;
				}

				SDL_Surface* textSurface10 = TTF_RenderText_Blended(font, balText.c_str(), textColor_black);
				if (textSurface10) {
					textTexture10 = SDL_CreateTextureFromSurface(renderer, textSurface10);
					SDL_FreeSurface(textSurface10);

					SDL_QueryTexture(textTexture10, NULL, NULL, &textRect10.w, &textRect10.h);
				}
			}
			
			std::ostringstream Bahstream;
			Bahstream << std::fixed << std::setprecision(5) << best_angle_high;
			std::string bahText = Bahstream.str() + " Degrees (higher arc, more air time)";

			if (bahText != prevBahText) {
				prevBahText = bahText;

				if (textTexture11) {
					SDL_DestroyTexture(textTexture11);
					textTexture11 = nullptr;
				}

				SDL_Surface* textSurface11 = TTF_RenderText_Blended(font, bahText.c_str(), textColor_black);
				if (textSurface11) {
					textTexture11 = SDL_CreateTextureFromSurface(renderer, textSurface11);
					SDL_FreeSurface(textSurface11);

					SDL_QueryTexture(textTexture11, NULL, NULL, &textRect11.w, &textRect11.h);
				}
			}
			
			//EVENT HANDLER
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					sdl_quit();
					running = false;
				}
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					SDL_Point mousePoint = { event.button.x, event.button.y };
					if (SDL_PointInRect(&mousePoint, &buttonRect13)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						writing_variable = 1.0;
						current_variable = &velocity;
						typing = true;
						SDL_StartTextInput();
						std::cout << "Enter muzzle velocity of the projectile (m/s)" << std::endl;	
					}
					if (SDL_PointInRect(&mousePoint, &buttonRect12)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						writing_variable = 2.0;
						current_variable = &target;
						typing = true;
						SDL_StartTextInput();
						std::cout << "Enter how far target away (meters)" << std::endl;	
					}
					if (SDL_PointInRect(&mousePoint, &buttonRect11)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						writing_variable = 3.0;
						current_variable = &diameter;
						typing = true;
						SDL_StartTextInput();
						std::cout << "Enter diameter of the projectile (mm)" << std::endl;	
					}
					if (SDL_PointInRect(&mousePoint, &buttonRect10)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						writing_variable = 4.0;
						current_variable = &mass;
						typing = true;
						SDL_StartTextInput();
						std::cout << "Enter weight of the projectile (kg)" << std::endl;	
					}
					if (SDL_PointInRect(&mousePoint, &buttonRect14)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						// Done typing
						writing_variable = 0.0;
						typing = false;
						SDL_StopTextInput();
						if (current_variable) {
							*current_variable = std::stod(inputText);
							std::cout << "Saved as: " << *current_variable << std::endl;
						}
						current_variable = nullptr;
						inputText.clear();
					}
					if (SDL_PointInRect(&mousePoint, &calculate_rect)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						calculate = true;
						error_handler = 0.0;
						
						if (velocity > 0 && target > 0 && diameter > 0 && mass > 0) {
							if (calculate == true) {
								double temp_kelvin = temp_celcius + 273.15;
		
								//ENVIRONMENTAL EFFECTS
								
								double air_density = air_pressure / (gas_constant * temp_kelvin);

								//PROJECTILE CALCULATION
								double radius = diameter / 2.0 / 1000.0;
								double area = M_PI * radius * radius;
								
								//TIME (SECONDS)
								double dt = 0.01;

								//SIMULATION
								for (double angle_deg = 1.0; angle_deg <= 89.0; angle_deg += 0.01) {
									//CONVERT ANGLE TO RADIANS
									double angle_rad = angle_deg * M_PI / 180.0;

									//START POSITION AND VELOCITY
									double x = 0.0;
									double y = 0.0;
									double vx = cos(angle_rad) * velocity;
									double vy = sin(angle_rad) * velocity;

									//SHELL SIM
									while (y >= 0.0) {
										
										//SPEED CALC.
										double speed = std::sqrt(vx * vx + vy * vy);

										//DRAG FORCE CALC.
										double drag_force = 0.5 * air_density * drag_coefficient * area * speed * speed;

										//CALC. ACCELERATION FROM DRAG
										double ax = -drag_force * (vx / speed) / mass;
										double ay = -gravity - (drag_force * (vy / speed) / mass);

										//VELOCITY UPDATE
										vx += ax * dt;
										vy += ay * dt;

										//POSITION UPDATE
										x += vx * dt;
										y += vy * dt;
										
									}
									
									double error = std::abs(x - target);
									
									if (error <= error_tolerance) {
										if (best_angle_low == 0.0) {
											best_angle_low = angle_deg;
											best_error_low = error;
										}
										best_angle_high = angle_deg;
										best_error_high = error;
									}
								}
								
								
								std::cout << std::fixed << std::setprecision(5) << "\n";
								if (best_error_high > 10 && best_error_low > 10) {
									std::cout << "! Your projectile can't reach to target without MAJOR errors.\n";
									std::cout << "Your projectile either too slow or too fast.\n";
									error_handler = 2.0;
								}
								else if (best_angle_high == best_angle_low) {
									std::cout << "For send your projectile to the target " << target << " meters away,\n";
									std::cout << "You have one launch angle:\n";
									std::cout << "\n";
									std::cout << best_angle_low << " degrees with " << best_error_low << " meters error.\n";	
								}
								else {
									std::cout << "For send your projectile to the target " << target << " meters away,\n";
									std::cout << "You have two launch angles:\n";
									std::cout << "\n";
									std::cout << "Lower trajectory, shorter air time:\n";
									std::cout << best_angle_low << " degrees with " << best_error_low << " meters error.\n";
									std::cout << "Higher trajectory, longer air time:\n";
									std::cout << best_angle_high << " degrees with " << best_error_high << " meters error.\n";	
									
								}
							calculate = false;
							}
						} else {
								std::cout << "Please enter all the information needed." << std::endl;
								error_handler = 1.0;
							}
					}
					
					if (SDL_PointInRect(&mousePoint, &exit_button_rect)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						screens = "MAIN_MENU";
						writing_variable = 0.0;
					}
				}
				if (event.type == SDL_TEXTINPUT && typing) {
					inputText += event.text.text;
				}
				if (event.type == SDL_KEYDOWN && typing) {
					if (event.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty()) {
						inputText.pop_back();
					}
					else if (event.key.keysym.sym == SDLK_RETURN) {
						// Done typing
						writing_variable = 0.0;
						typing = false;
						SDL_StopTextInput();
						if (current_variable) {
							*current_variable = std::stod(inputText);
							std::cout << "Saved as: " << *current_variable << std::endl;
						}
						current_variable = nullptr;
						inputText.clear();
					}
				}
			}
		
			
			//renderer start
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);
			
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			
			SDL_RenderCopy(renderer, main_menu, nullptr, &exit_button_rect);
			SDL_RenderCopy(renderer, ew, nullptr, &buttonRect10);
			SDL_RenderCopy(renderer, et, nullptr, &buttonRect11);
			SDL_RenderCopy(renderer, ehfta, nullptr, &buttonRect12);
			SDL_RenderCopy(renderer, emv, nullptr, &buttonRect13);
			SDL_RenderCopy(renderer, calculatee, nullptr, &calculate_rect);
			SDL_RenderCopy(renderer, enter_button, nullptr, &buttonRect14);
			
			if (error_handler == 1.0) {
				SDL_RenderCopy(renderer, warning1, nullptr, &buttonRect15);
			}
			
			if (error_handler == 2.0) {
				SDL_RenderCopy(renderer, warning, nullptr, &buttonRect15);
			}
			
			
			SDL_RenderCopy(renderer, env_variable_text.texture, NULL, &env_variable_text.rect);
			SDL_RenderCopy(renderer, textTexture4, NULL, &textRect4);
			SDL_RenderCopy(renderer, textTexture5, NULL, &textRect5);
			SDL_RenderCopy(renderer, textTexture6, NULL, &textRect6);
			SDL_RenderCopy(renderer, entering_text.texture, NULL, &entering_text.rect);
			SDL_RenderCopy(renderer, calc_results_text.texture, NULL, &calc_results_text.rect);
			SDL_RenderCopy(renderer, textTexture10, NULL, &textRect10);
			SDL_RenderCopy(renderer, textTexture11, NULL, &textRect11);
			SDL_RenderCopy(renderer, gravity_text_texture, NULL, &GravityRect);
			SDL_RenderCopy(renderer, gasconstant_text_texture, NULL, &GasConstantRect);
			
			
			if (writing_variable == 1.0) {
				SDL_RenderCopy(renderer, writing_text_1.texture, NULL, &writing_text_1.rect);
			}
			
			if (writing_variable == 2.0) {
				SDL_RenderCopy(renderer, writing_text_launch_2.texture, NULL, &writing_text_launch_2.rect);
			}
			
			if (writing_variable == 3.0) {
				SDL_RenderCopy(renderer, writing_text_3.texture, NULL, &writing_text_3.rect);
			}
			
			if (writing_variable == 4.0) {
				SDL_RenderCopy(renderer, writing_text_4.texture, NULL, &writing_text_4.rect);
			}
			
			if (!inputText.empty()) {
				SDL_Surface* textSurface = TTF_RenderText_Blended(font, inputText.c_str(), textColor_black);
				SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
				SDL_Rect textRect = {130, 900, textSurface->w, textSurface->h};
				SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
				SDL_FreeSurface(textSurface);
				SDL_DestroyTexture(textTexture);
			}
			
			//renderer end
			SDL_RenderPresent(renderer);
			SDL_Delay(50);
			
		}
		if (screens == "CHANGE_E_VARIABLES") {
			
			//EVENT HANDLER
			while (SDL_PollEvent(&event)) {
				SDL_Point mousePoint = { event.button.x, event.button.y };
				if (event.type == SDL_QUIT) {
					sdl_quit();
					running = false;
				}
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					
					if (SDL_PointInRect(&mousePoint, &exit_button_rect)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						writing_variable = 0.0;
						screens = "MAIN_MENU";
					}
					
					if (SDL_PointInRect(&mousePoint, &cerrort_button_rect)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						writing_variable = 5.0;
						current_variable = &error_tolerance;
						typing = true;
						SDL_StartTextInput();
						std::cout << "Enter error tolerance (meters)" << std::endl;	
					}
					if (SDL_PointInRect(&mousePoint, &cairp_button_rect)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						writing_variable = 7.0;
						current_variable = &air_pressure;
						typing = true;
						SDL_StartTextInput();
						std::cout << "Enter air pressure (pascals)" << std::endl;	
					}
					if (SDL_PointInRect(&mousePoint, &cgravity_button_rect)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						writing_variable = 8.0;
						current_variable = &gravity;
						typing = true;
						SDL_StartTextInput();
						std::cout << "Enter gravity (m/s2)" << std::endl;	
					}
					if (SDL_PointInRect(&mousePoint, &cconstant_button_rect)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						writing_variable = 9.0;
						current_variable = &gas_constant;
						typing = true;
						SDL_StartTextInput();
						std::cout << "Enter gas constant per kilogram per kelvin (J/(kg*K))" << std::endl;	
					}
					
					if (SDL_PointInRect(&mousePoint, &enter_button_1_rect)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						// Done typing
						typing = false;
						SDL_StopTextInput();
						if (current_variable) {
							*current_variable = std::stod(inputText);
							std::cout << "Saved as: " << *current_variable << std::endl;
						}
						current_variable = nullptr;
						inputText.clear();
					}
				}
				if (event.type == SDL_TEXTINPUT && typing) {
					inputText += event.text.text;
				}
				if (event.type == SDL_KEYDOWN && typing) {
					if (event.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty()) {
						inputText.pop_back();
					}
					else if (event.key.keysym.sym == SDLK_RETURN) {
						// Done typing
						writing_variable = 0.0;
						typing = false;
						SDL_StopTextInput();
						if (current_variable) {
							*current_variable = std::stod(inputText);
							std::cout << "Saved as: " << *current_variable << std::endl;
						}
						current_variable = nullptr;
						inputText.clear();
					}
				}
			}
		
			
			//renderer start
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);
			
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			
			SDL_RenderCopy(renderer, main_menu, nullptr, &exit_button_rect);
			SDL_RenderCopy(renderer, c_air_pressure, nullptr, &cairp_button_rect);
			SDL_RenderCopy(renderer, c_error_tolerance, nullptr, &cerrort_button_rect);
			SDL_RenderCopy(renderer, c_gravity, nullptr, &cgravity_button_rect);
			SDL_RenderCopy(renderer, c_gas_constant, nullptr, &cconstant_button_rect);
			SDL_RenderCopy(renderer, enter_button, nullptr, &enter_button_1_rect);
			
			SDL_RenderCopy(renderer, env_variable_text.texture, NULL, &env_variable_text.rect);
			SDL_RenderCopy(renderer, textTexture4, NULL, &textRect4);
			SDL_RenderCopy(renderer, textTexture5, NULL, &textRect5);
			SDL_RenderCopy(renderer, textTexture6, NULL, &textRect6);
			SDL_RenderCopy(renderer, gravity_text_texture, NULL, &GravityRect);
			SDL_RenderCopy(renderer, gasconstant_text_texture, NULL, &GasConstantRect);	
			SDL_RenderCopy(renderer, entering_text.texture, NULL, &entering_text.rect);
			
			if (writing_variable == 5.0) {
				SDL_RenderCopy(renderer, cng_env_text_3.texture, NULL, &cng_env_text_3.rect);
			}
			
			if (writing_variable == 7.0) {
				SDL_RenderCopy(renderer, cng_env_text_5.texture, NULL, &cng_env_text_5.rect);
			}
			
			if (writing_variable == 8.0) {
				SDL_RenderCopy(renderer, cng_env_text_1.texture, NULL, &cng_env_text_1.rect);
			}
			
			if (writing_variable == 9.0) {
				SDL_RenderCopy(renderer, cng_env_text_2.texture, NULL, &cng_env_text_2.rect);
			}
			
			if (!inputText.empty()) {
				SDL_Surface* textSurface = TTF_RenderText_Blended(font, inputText.c_str(), textColor_black);
				SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
				SDL_Rect textRect = {130, 900, textSurface->w, textSurface->h};
				SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
				SDL_FreeSurface(textSurface);
				SDL_DestroyTexture(textTexture);
			}
			
			
			SDL_RenderPresent(renderer);
			SDL_Delay(50);
			
		}
		if (screens == "MAIN_MENU") {
			//EVENT HANDLER
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					sdl_quit();
					running = false;
				}
				
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					SDL_Point mousePoint = { event.button.x, event.button.y };
					if (SDL_PointInRect(&mousePoint, &menu_button_1_rect)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						screens = "LAUNCH_ANGLE";
						}
					//arrow-like shot button
					if (SDL_PointInRect(&mousePoint, &menu_button_2_rect)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						screens = "ARROW";
						}
					//change e. variables button
					if (SDL_PointInRect(&mousePoint, &menu_button_3_rect)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						screens = "CHANGE_E_VARIABLES";
						}
					//exit button
					if (SDL_PointInRect(&mousePoint, &menu_button_4_rect)) {
						Mix_PlayChannel(-1, buttonSound, 0);
						running = false;
						}
				}
			}

			//RENDERER START
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, ILE_logo, nullptr, &ILE_logo_rect);
			
			SDL_RenderCopy(renderer, launch_angle_calc_button, nullptr, &menu_button_1_rect);
			SDL_RenderCopy(renderer, ashot_arrow, nullptr, &menu_button_2_rect);
			SDL_RenderCopy(renderer, change_e_variable_button, nullptr, &menu_button_3_rect);
			SDL_RenderCopy(renderer, exit_button, nullptr, &menu_button_4_rect);
			
			SDL_RenderCopy(renderer, menu_text1.texture, NULL, &menu_text1.rect);
			SDL_RenderCopy(renderer, menu_text2.texture, NULL, &menu_text2.rect);
			SDL_RenderCopy(renderer, menu_text3.texture, NULL, &menu_text3.rect);
			SDL_RenderCopy(renderer, menu_text4.texture, NULL, &menu_text4.rect);

			SDL_RenderPresent(renderer);
			SDL_Delay(50);
		}
	}
	sdl_quit();
	running = false;
	return 0;
}
