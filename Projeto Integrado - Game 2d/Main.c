//bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>



//function int main
int main() {
	
	int area = 0;
	bool sair = false;
	//definindo o tamanho da tela 
	ALLEGRO_DISPLAY *display = NULL;

	ALLEGRO_TIMER* timer = NULL;
	//criando o ponteiro para um imagem
	ALLEGRO_BITMAP *imagem = NULL;
	ALLEGRO_BITMAP *btnAzul = NULL;
	ALLEGRO_BITMAP *btnVermelho = NULL;
	ALLEGRO_BITMAP* btnAmarelo = NULL;
	ALLEGRO_BITMAP* btnVerde = NULL;


	//criando ponterio para a font
	ALLEGRO_FONT *font = NULL;
	
	//fila de eventos
	ALLEGRO_EVENT_QUEUE *eventQueue = NULL;

	//samples
	ALLEGRO_SAMPLE *sampleAzul = NULL;
	ALLEGRO_SAMPLE *sampleVermelho = NULL;
	ALLEGRO_SAMPLE* sampleAmarelo = NULL;
	ALLEGRO_SAMPLE* sampleVerde = NULL;

	//input para digitar o texto
	//printf("Digite o texto que vc deseja escrever na tela do allegro: ");
	//gets(texto);

	//inicializando o Allegro
	al_init();

	// Inicializa o add-on para utilização de imagens
	al_init_image_addon();

	//inicliazar o addon-font
	al_init_font_addon();

	al_init_ttf_addon();

	al_install_audio();
	
	al_init_acodec_addon();
	
	al_reserve_samples(1);

	al_install_mouse();
	
	al_install_keyboard();


	

	//import sons
	sampleAmarelo = al_load_sample("sounds/arrow_hit.ogg");
	sampleVermelho = al_load_sample("sounds/axe_hit.ogg");
	sampleAzul = al_load_sample("sounds/orc_death.ogg");
	sampleVerde = al_load_sample("sounds/arrow_miss.ogg");

	//configurando a font
	font = al_load_font("fonts/arial.ttf", 70, 0);
	
	if (!font) {
		al_destroy_display(display);
		printf("Falha ao carregar fonte");
		return -1;
	}

	//tamanho da janela
	display = al_create_display(800, 600);

	timer = al_create_timer(1 / 60);
	//title dispaly
	al_set_window_title(display, "Joguinho BEM NICE");
	
	//importando a imagem 
	imagem = al_load_bitmap("imagens/imagem.bmp");
	
	//criar bitmaps
	btnAzul = al_create_bitmap(80, 80);
		al_set_target_bitmap(btnAzul);
		al_clear_to_color(al_map_rgb(0, 0, 255));
	
	btnVermelho = al_create_bitmap(80, 80);
		al_set_target_bitmap(btnVermelho);
		al_clear_to_color(al_map_rgb(255, 0, 0));

	btnAmarelo = al_create_bitmap(80, 80);
		al_set_target_bitmap(btnAmarelo);
		al_clear_to_color(al_map_rgb(255, 255, 0));
	
	btnVerde = al_create_bitmap(80, 80);
		al_set_target_bitmap(btnVerde);
		al_clear_to_color(al_map_rgb(0, 255, 0));

	al_start_timer(timer);
	//definindo fila de eventos
	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	//inicializar 

	

	//draw image
	//al_draw_bitmap(imagem, 0, 0, 0);



	//flipando o display
	int x = 0;
	char letra[2];
	char texto[100] = "";
	
	//guarda o título da caixa de texto
	char tcaixa[50] = "Atencao";
	//o título da mensagem dentro da caixa
	char titulo[100] = "Sair do Game";
	//o conteúdo da mensagem exibida
	char textoCaixa[200] = "Voce deseja sair do jogo?";
	while (!sair){
		
		

		//aguardando event
		ALLEGRO_EVENT evento;
		al_wait_for_event(eventQueue, &evento);
		
		
		//pintar o background
		al_set_target_bitmap(al_get_backbuffer(display));
		al_clear_to_color(al_map_rgb(250, 250, 250));

		al_draw_text(font, al_map_rgb(0, 0, 0), 50, 250, ALLEGRO_ALIGN_LEFT, texto);
		
		//desenha bitmaps que serao clicados
		al_draw_bitmap(btnAmarelo, 50, 50, 0);
		al_draw_bitmap(btnVermelho, 200, 50, 0);
		al_draw_bitmap(btnVerde, 350, 50, 0);
		al_draw_bitmap(btnAzul, 500, 50, 0);


		al_flip_display();


		if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
			if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
				//backspace, volta uma posicao no texto
				if (texto[strlen(texto) - 1] > -1)
				{
					texto[strlen(texto) - 1] = '\0';
				}
				
			}
			else if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				int r = al_show_native_message_box(NULL, tcaixa, titulo, textoCaixa, NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);
				if (r == 1)
				{
					sair = true;
				}
			}
			else
			{
				int pos = strlen(texto) - 1;
				*letra = evento.keyboard.unichar;

				texto[strlen(texto)] = letra[0];
			}
		}
		//draw font


		else if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			
				if (evento.mouse.y >= 50 && evento.mouse.y <= 130)
				{
					if (evento.mouse.x >= 50 && evento.mouse.x <= 130)
						al_play_sample(sampleAmarelo, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					else if (evento.mouse.x >= 200 && evento.mouse.x <= 280)
					{
						al_play_sample(sampleVermelho, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
					else if (evento.mouse.x >= 350 && evento.mouse.x <= 430)
					{
						al_play_sample(sampleVerde, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
					else if (evento.mouse.x >= 500 && evento.mouse.x <= 580)
					{
						al_play_sample(sampleAzul, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					}

				}
				else
					area = 0;
			
		}

		else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			sair = true;
		}

	}
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_sample(sampleAzul);
	al_destroy_sample(sampleVermelho);
	al_destroy_sample(sampleAmarelo);
	al_destroy_sample(sampleVerde);
	al_destroy_event_queue(eventQueue);
	al_destroy_font(font);
	al_destroy_bitmap(imagem);
	al_destroy_bitmap(btnAmarelo);
	al_destroy_bitmap(btnVerde);
	al_destroy_bitmap(btnAzul);
	al_destroy_bitmap(btnVermelho);
	al_destroy_display(display);
	system("pause");
	return 0;
}
