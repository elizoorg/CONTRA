#include "Block.h"

Block::Block()
{
}

Block::~Block()
{
}


void Block::set(int x, int y, int id)
{
	border.x = x;
	border.y = y;
	blockid = id;
}

SDL_Rect Block::getRect()
{
	return border;
}

void Block::Render(SDL_Renderer* render,SDL_Texture* blocks,vec2i camerax)
{
	clipRect.x = border.x-camerax.x;
	clipRect.y = border.y-camerax.y;
    SDL_SetRenderDrawColor(render, 255, 0, 0, 0);
    SDL_RenderDrawRect(render, &clipRect);
	SDL_RenderCopy(render, blocks, &source, &clipRect);
}


int check_bcollisionV(SDL_Rect A, SDL_Rect B)
{

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
 
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }
 
    if (bottomA > topB)return 2;

    if (topA > bottomB) return 1;
   
   

   
}
int check_bcollisionH(SDL_Rect A, SDL_Rect B)
{

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }
    
    if ((rightA>leftB && rightA<rightB)  && bottomA>bottomB) return 2;
    if ((leftA < rightB  && leftA > leftB) && bottomA > bottomB) return 1;

} 


int check_bcollision(SDL_Rect A, SDL_Rect B)
{

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    if (leftB < leftA || rightB > rightA) return 2;
    if (topB > topA || bottomB < bottomA) return 1;

    return 1;

}