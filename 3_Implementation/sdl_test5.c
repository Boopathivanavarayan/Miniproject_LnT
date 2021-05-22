#include <SDL2/SDL.h>
#include <stdio.h>
typedef struct
{
  int x, y;
} Probe;

char pattern1[7][25]={
    {"-------------------------"},
    {"|------------------------"},
    {"#######------------------"},
    {"|------####--------------"},
    {"-----------#######-------"},
    {"------------------#######"},
    {"-------------------------"}
};

int processEvents(SDL_Window *window, Probe *up, Probe *down)
{
  SDL_Event event;
  int done = 0;
  
  while(SDL_PollEvent(&event))
  {  
    switch(event.type)
    {
      case SDL_WINDOWEVENT_CLOSE:
      {
        if(window)
        {
          SDL_DestroyWindow(window);
          window = NULL;
          done = 1;
        }
      }
      break;
      case SDL_KEYDOWN:
      {
        switch(event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
            done = 1;
          break;
        }
      }
      break;
      case SDL_QUIT:
        //quit out of the game
        done = 1;
      break;
    }
  }
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if(state[SDL_SCANCODE_A])
  {
    pattern1[up->x][up->y] = '-';   
    up->y -= 1;
    pattern1[up->x][up->y] = '|'; 

  }
  if(state[SDL_SCANCODE_J])
  {
    pattern1[down->x][down->y] = '-';   
    down->y -= 1;
    pattern1[down->x][down->y] = '|';
    return done; 
  }
    
  
 

  if(state[SDL_SCANCODE_D])
  {
    pattern1[up->x][up->y] = '-';   
    up->y += 1;
    pattern1[up->x][up->y] = '|'; 
  }

  if(state[SDL_SCANCODE_L])
  {
    pattern1[down->x][down->y] = '-';   
    down->y += 1;
    pattern1[down->x][down->y] = '|'; 
    return done;
  }
    
   

  if(state[SDL_SCANCODE_W])
  {
    pattern1[up->x][up->y] = '-';   
    up->x -= 1;
    pattern1[up->x][up->y] = '|'; 

  }

  if(state[SDL_SCANCODE_I])
  {
    pattern1[down->x][down->y] = '-';   
    down->x -= 1;
    pattern1[down->x][down->y] = '|'; 
    return done;
  }
   
  
  if(state[SDL_SCANCODE_S])
  {
    pattern1[up->x][up->y] = '-';   
    up->x += 1;
    pattern1[up->x][up->y] = '|'; 
    return done;
  }
  if(state[SDL_SCANCODE_K])
   {
    pattern1[down->x][down->y] = '-';   
    down->x += 1;
    pattern1[down->x][down->y] = '|'; 
    return done;
   }
    
       
  if(state[SDL_SCANCODE_ESCAPE])
  {
      done = 1;
      return done;
  }
  
}

void doRender(SDL_Renderer *renderer, Probe *up, Probe *down)
{
  //set the drawing color to blue
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  
  //Clear the screen (to blue)
  SDL_RenderClear(renderer);
  
  //set the drawing color to white
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  /*
  SDL_Rect rect = { up->x, up->y, 200, 200 };
  SDL_RenderFillRect(renderer, &rect);
  */
  SDL_Rect rect[7][25];
  for(int i=0;i<7;i++){
      for(int j=0;j<25;j++){
          
          if(pattern1[i][j] == '|'){
              //rect[i*j]={50+i*20,50+j*20,10,10};
                rect[i][j].x = 50+j*20;
                rect[i][j].y = 50+i*20;
                rect[i][j].h = 10;
                rect[i][j].w = 10;
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rect[i][j]);
          }
          else if(pattern1[i][j] == '-'){
                rect[i][j].x = 50+j*20;
                rect[i][j].y = 50+i*20;
                rect[i][j].h = 10;
                rect[i][j].w = 10;
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &rect[i][j]);
          }
          else if(pattern1[i][j] == '#'){
                rect[i][j].x = 50+j*20;
                rect[i][j].y = 50+i*20;
                rect[i][j].h = 10;
                rect[i][j].w = 10;
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(renderer,&rect[i][j]);
          }
      }
  }
  
  //We are done drawing, "present" or show to the screen what we've drawn
  SDL_RenderPresent(renderer);
}


void graphics(void){
  SDL_Window *window;                    // Declare a window
  SDL_Renderer *renderer;                // Declare a renderer
  
  SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
  
  Probe up,down;
  up.x = 1;
  up.y = 0;
  down.x = 3;
  down.y = 0;
  
  //Create an application window with the following settings:
  window = SDL_CreateWindow("Game Window",                     // window title
                            SDL_WINDOWPOS_UNDEFINED,           // initial x position
                            SDL_WINDOWPOS_UNDEFINED,           // initial y position
                            640,                               // width, in pixels
                            640,                               // height, in pixels
                            0                                  // flags
                            );
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  
  // The window is open: enter program loop (see SDL_PollEvent)
  int done = 0;
  
  //Event loop
  while(!done)
  {
    //Check for events
    done = processEvents(window, &up, &down);
    
    //Render display
    doRender(renderer, &up, &down);
    
    //don't burn up the CPU
    SDL_Delay(75);
  }
  
  
  // Close and destroy the window
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  
  // Clean up
  SDL_Quit();
}

int main(int argc, char *argv[]){
    graphics();
    return 0;
}