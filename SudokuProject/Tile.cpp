#include "Tile.h"

Tile::Tile(int r, int c) {
	row = r;
	col = c;
	square = findSquare(r, c);
	val = -1;
	potential.set();
}

Tile::Tile(int r, int c, int v) {
	row = r;
	col = c;
	square = findSquare(r, c);
	val = v;
	potential.reset();
}

bool Tile::hasVal() {
   if (val == -1) {
      return false;
   }
   else {
      return true;
   }
}

int Tile::findVal() {
   int val = -1;
   if (potential.count() == 1) {
      int count = 0;
      while (val == -1 || count < 9) {
         if (potential.test(count)) {
            val = count + 1;
         }
         count++;
      }
   }
   return val;
}

void Tile::setVal(int v) {
   val = v;
   potential.reset();
}


void Tile::removePotential(int v) {
	potential.reset(v-1);
}

void Tile::setPotentialAs(int v) {
	potential.reset();
	potential.set(v-1);
}

bool Tile::hasSinglePotential() {
	if (potential.count() == 1) {
		return true;
	}
	else {
		return false;
	}
}

bool Tile::hasPotential(int v) {
	return potential.test(v-1);
}


bool Tile::hasBeenQueued() {
	return wasQueued;
}

void Tile::setQueueState(bool flag) {
   wasQueued = flag;
}

int Tile::findSquare(int r, int c) {
   int sq = 0;
   if (r < 4) {
      if (c < 4) {
         sq = 1;
      }
      else if (c > 3 && c < 7) {
         sq = 2;
      }
      else if (c > 6) {
         sq = 3;
      }
   }
   else if (r > 3 && r < 7) {
      if (c < 4) {
         sq = 4;
      }
      else if (c > 3 && c < 7) {
         sq = 5;
      }
      else if (c > 6) {
         sq = 6;
      }
   }
   else if (r > 6) {
      if (c < 4) {
         sq = 7;
      }
      else if (c > 3 && c < 7) {
         sq = 8;
      }
      else if (c > 6) {
         sq = 9;
      }
   }
   return sq;
}