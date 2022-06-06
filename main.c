#include <stdio.h> // Import libaries
#include <stdlib.h> // Malloc
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h> // Convert mixed case string into lowercases

/*

We need:
    * pokemonList
       * pokemonName [CHAR] [20];
       * pokemonType [CHAR] [20];
       * pokemonAbility [CHAR] [20];
    * playerList
       * playerName
       * pokemonCaught
    * Pokedex
       * Contains 
    * Linked list style

    * Voids to return functions from the node

    * main:
      * AddPlayerToList
      * DisplayPlayerDetails
      * PokemonToList
      * FindPokemon
      * PokemonToPlayer

 */

typedef struct PokemonNode { // Structure PokemonNode (old)
  char pokemonName [20]; //Pokemon variables
  char pokemonType [20];
  char pokemonAbility [30];
  struct PokemonNode * lPokemon, * rPokemon; // Binary tree Structure for left and right pokemon.

} PokemonNode; // PokemonNode (new, use this.)

typedef struct CaughtPokemonNode {
  char * pokemonName;
  struct CaughtPokemonNode * nextCaughtPokemon; 

} CaughtPokemonNode;

// LL Node to store individual player/trainer.
typedef struct PlayerNode { 
  char playerName[30];
  struct PlayerNode * nextPlayer; // LL nextPlayer

} PlayerNode;

typedef struct pokedex { 
  struct PokemonNode * pokemonHead; // Head of X node.
  struct PlayerNode * playerHead;

} pokedex;

pokedex * NewPokedex ();

// Defind functions to be used in the main.
PokemonNode * NewPokemonNode(char * name, char * type, char * ability);
void PokemonToList( pokedex *Pokedex, char * name, char * type, char * ability);
void DisplayPokemonDetails(pokedex * Pokedex, char * name);
// Void is used to return the function. Makes the pointer universal. Also create nodes
PokemonNode * FindPokemon( pokedex * Pokedex, char * name ); // This finds the pokemin by pokemonName as name.
void AddPlayerToList(pokedex *Pokedex, char * name);

PlayerNode * FindPlayer(pokedex *Pokedex, char *name);

CaughtPokemonNode * NewCaughtPokemonNode(pokedex * Pokedex, char * pokemonName);
void DisplayPlayerDetails(pokedex * Pokedex, char * name);
int getCaughtPokemonLength(PlayerNode * player);
void PokemonToPlayer(pokedex *Pokedex, char * playerName, char * pokemonName);

// Displays head of the node of:
void DisplayHeadPokeNode(pokedex * Pokedex, char * pokemonName);

// New pokedex Structure
pokedex * NewPokedex () {
pokedex * newPokedex = NULL;
newPokedex = (pokedex*)malloc(sizeof(pokedex)); // Allocate memory size needed
newPokedex -> pokemonHead = NULL; // set pokemonHead & playerHead to NULL
newPokedex -> playerHead = NULL;
free(newPokedex);

return newPokedex;

}

// This will add PlayerNode into the pokedex linked list
void PokemonToList( pokedex *Pokedex, char * name, char * type, char * ability) {
  PokemonNode * newPokemon = NewPokemonNode(name, type, ability); // Create new node
  if (Pokedex -> pokemonHead == NULL) { // If tree is empty, then create new PokemonNode
    Pokedex -> pokemonHead = newPokemon;
    return;

  }

  else { // If search tree is not empty, put new node at end
    PokemonNode * current = NULL;
    current = Pokedex -> pokemonHead;
    bool check = false;

    while (!check) {
      int first = strcasecmp(current -> pokemonName, name); 
      if (first > 0) {
        if (current -> lPokemon != NULL) { // If lPokemon is NULL then move.
          current = current -> lPokemon;
        }

        else { // Else if next node is NULL then skip to the next one
          current -> lPokemon = newPokemon;
          break;

        }
      }

      else {
        if (current -> rPokemon != NULL) {
          current = current -> rPokemon;

        }

        else {
          current -> rPokemon = newPokemon; 
          break;

        }
      }
    }
  }
  return;
}

PokemonNode * FindPokemon( pokedex * Pokedex, char * name ) { // Finding pokemon.
  if (Pokedex -> pokemonHead == NULL) {  // If check there is no pokemon in pokedex tree. Then respond with NULL.
      return NULL;
    }
  
  PokemonNode * current = NULL; // Start searching by Preorder (Root, left & right)
  current = Pokedex -> pokemonHead;

  while (current != NULL) {
    if (current == NULL) { // Check paramaters 

    }
    
    int firstCheck = strcasecmp(current -> pokemonName, name);
    if (firstCheck == 0) { 
      return current;
    }

    else if (firstCheck > 0) {
      current = current -> lPokemon; // go to left node
    }

    else {
      current = current -> rPokemon; // go to right node
    }

  }
  return NULL;

}

// This displays the pokemon
void DisplayPokemonDetails(pokedex * Pokedex, char * name) {
  PokemonNode * pokemon = FindPokemon(Pokedex, name);

  printf("\nPokemon Name: %s\nType: %s\nAbility: %s\n", 
  pokemon -> pokemonName, pokemon -> pokemonType, pokemon -> pokemonAbility);
  
  return;

}

// Create new node for Pokemon
PokemonNode *NewPokemonNode(char * name, char * type, char * ability) { 
  PokemonNode * newNode = NULL;

  newNode = (PokemonNode*)malloc(sizeof(PokemonNode)); // Allocates memory

  if (newNode != NULL) {
    strcpy(newNode -> pokemonName, name); // Copy string pointer.
    strcpy(newNode -> pokemonType, type);
    strcpy(newNode -> pokemonAbility, ability);
    newNode -> lPokemon = newNode -> rPokemon = NULL; 

  }

  return newNode;

}


PlayerNode * NewPlayerNode (char * name) { 
  PlayerNode * newNode = NULL;
  newNode = malloc(sizeof(PlayerNode)); // Allocates memory to the size of the how many in player node.
  
  if (newNode != NULL) { // This statement finds player in memory.
    strcpy(newNode -> playerName, name);
    struct PlayerNode * nextPlayer = NULL; // if the if statement is comment out all players will be NULL.
  }

  return newNode; 
}

void AddPlayerToList(pokedex * Pokedex, char * name) {
  PlayerNode * newPlayer = NewPlayerNode(name);
  if (Pokedex -> playerHead == NULL) { // Check if PlayerNode was made, if not create new one as head of the list.
    Pokedex -> playerHead = newPlayer;
    return;
  }

  else { // Else if there is a head, then start traversing 
    PlayerNode * current = NULL;
    current = Pokedex -> playerHead;
    while (current != NULL) { // If next node lost or does not exit then set new player. Navigate though the list.
      if (current -> nextPlayer == NULL) { // If its last node then NULL.

        current -> nextPlayer = newPlayer;  
        return;
      }

      else {
        current = current -> nextPlayer;  // Go to next link.
      }
    }
  }
  return; // If data is found, return the current link.
}

PlayerNode * FindPlayer(pokedex * Pokedex, char * name) { // Finding players inside the pokedex
  if (Pokedex -> playerHead == NULL) { // If there is no pokemon in the pokedex then set it to NULL. 

    return NULL;
  }

// This will traverse though the pokedex playerNode linked list starting it's head firstCheck.
  PlayerNode * current = Pokedex -> playerHead;
  while (current != NULL) {

    int stringsEqual = strcasecmp(current -> playerName, name);
    if (stringsEqual == 0) {

      return current;
    }

    else { // else if player doesn't match ten skip to the next node.

      current = current -> nextPlayer;
    }
  }
  return NULL; 
}

// Displays player details
void DisplayPlayerDetails(pokedex * Pokedex, char *name) { // Find details in the pokedex
  PokemonNode * pokemon = FindPokemon(Pokedex, name);
  printf("\nPlayer Name: %s\n", name); // Find players name
  
  return;
}

// Displays pokemon to player
void PokemonToPlayer(pokedex * Pokedex, char * playerName, char * pokemonName) {
    PlayerNode * selectedPlayer = FindPlayer(Pokedex, playerName);
    printf("Player: %s\n", selectedPlayer -> playerName);
    printf("Pokemon: %s\n\n", pokemonName); 

    return;
}

void DisplayHeadPokeNode(pokedex * Pokedex, char * pokemonName) {
  printf("Head node of Pokemon: %s\n", Pokedex -> pokemonHead -> pokemonName);

}

int main(void) {
  pokedex *mainPokedex = NewPokedex();

  // Add Players to the pokedex
  AddPlayerToList(mainPokedex, "Ash");
  AddPlayerToList(mainPokedex, "Misty");
  AddPlayerToList(mainPokedex, "Dawn");
  AddPlayerToList(mainPokedex, "Brock");

  printf("\n\nList player:\n\n");
  DisplayPlayerDetails(mainPokedex, "Ash");
  DisplayPlayerDetails(mainPokedex, "Misty");
  DisplayPlayerDetails(mainPokedex, "Dawn");
  DisplayPlayerDetails(mainPokedex, "Brock");

  printf("\n\nList of pokemon by name, type & ability:\n\n");
  // Add Pokemon to the pokedex
  PokemonToList(mainPokedex, "Bulbasaur", "Grass", "Overgrow"); 
  PokemonToList(mainPokedex, "Charmander", "Fire", "Blaze");
  PokemonToList(mainPokedex, "Squirtle", "Water", "Torrent");
  PokemonToList(mainPokedex, "Butterfree", "Bug", "Compound Eyes");
  PokemonToList(mainPokedex, "Pidgey", "Normal", "Tangled Feet");
  PokemonToList(mainPokedex, "Vgnomoth", "Bug", "Shield Dust");
  PokemonToList(mainPokedex, "Poliwag", "Water", "Water Absorb");
  PokemonToList(mainPokedex, "Psyduck", "Water", "Damp");


  FindPokemon(mainPokedex, "Bulbasaur");
  FindPokemon(mainPokedex, "Charmander");
  FindPokemon(mainPokedex, "Squirtle");
  FindPokemon(mainPokedex, "Butterfree");
  FindPokemon(mainPokedex, "Pidgey");
  FindPokemon(mainPokedex, "Vgnomoth");
  FindPokemon(mainPokedex, "Poliwag");
  FindPokemon(mainPokedex, "Psyduck");

  // Displays Pokemon name
  DisplayPokemonDetails(mainPokedex, "Bulbasaur");
  DisplayPokemonDetails(mainPokedex, "Charmander");
  DisplayPokemonDetails(mainPokedex, "Squirtle");
  DisplayPokemonDetails(mainPokedex, "Butterfree");
  DisplayPokemonDetails(mainPokedex, "Pidgey");
  DisplayPokemonDetails(mainPokedex, "Vgnomoth");
  DisplayPokemonDetails(mainPokedex, "Poliwag");
  DisplayPokemonDetails(mainPokedex, "Psyduck");


  printf("\n\nList of pokemon caught by player:\n\n");
  PokemonToPlayer(mainPokedex, "Ash", "Charmander");
  PokemonToPlayer(mainPokedex, "Ash", "Pidgey");
  PokemonToPlayer(mainPokedex, "Ash", "Zoroark");
  PokemonToPlayer(mainPokedex, "Misty", "Squirtle");
  PokemonToPlayer(mainPokedex, "Dawn", "Poliwag");
  PokemonToPlayer(mainPokedex, "Dawn", "Pidgey");
  PokemonToPlayer(mainPokedex, "Brock", "Psyduck");

  // Displayhead node in Pokemon node
  printf("\n\nDisplays head nodes of:\n\n");
  DisplayHeadPokeNode(mainPokedex, "");

  return 0;
}
