#include <iostream>

class Vecteur
{
	private:
		int Taille;
		float *T;
	public:
		Vecteur();
		Vecteur(int);
		Vecteur(const Vecteur&);
		~Vecteur();
		void Affiche();
		bool TailleEgale(const Vecteur&);
		Vecteur Somme(const Vecteur&);
		float& operator[](int);
		friend float operator*(const Vecteur&, const Vecteur&);
		Vecteur operator*(float);
		friend Vecteur operator*(float, const Vecteur&);
		Vecteur& operator=(const Vecteur&);
		bool operator==(const Vecteur&);
		bool operator!=(const Vecteur&);
		Vecteur operator+(float);
};

#include <iostream>
#include "Vecteur.h"

int MAX(int a, int b) {
	return (a > b) ? a : b;
}

Vecteur::Vecteur() {
	Taille = 0;
	T = nullptr;
}

Vecteur::Vecteur(int taille) {
	Taille = taille;
	T = new float[Taille];
	int i=0;
	while (i < Taille) {
		T[i] = 0;
		i++;
	}
}

Vecteur::Vecteur(const Vecteur& v) {
	Taille = v.Taille;
	int i=0;
	T = new float[Taille];
	while (i < Taille) {
		T[i] = v.T[i];
		i++;
	}
}

Vecteur::~Vecteur() {
	delete[] T;
}

void Vecteur::Affiche() {
	int i=0;
	while (i < Taille) {
		std::cout << T[i] << " ";
		i++;
	}
	std::cout << std::endl;
}

bool Vecteur::TailleEgale(const Vecteur& v) {
	return (Taille == v.Taille);
}

Vecteur Vecteur::Somme(const Vecteur& v) {
	Vecteur vec;
	if (!TailleEgale(v)) {
		return vec;
	}
	int i=0;
	while (i < Taille) {
		vec[i] = T[i] + v.T[i];
	}
	return vec;
}

float& Vecteur::operator[](int index) {
	return T[index];
}

float operator*(const Vecteur& v1, const Vecteur& v2) {
	if (v1.Taille != v2.Taille) {
		return 0;
	}
	float p = 0;
	int i=0;
	while (i < v1.Taille) {
		p += v1.T[i] * v2.T[i];
		i++;
	}
	return p;
}

Vecteur Vecteur::operator*(float k) {
	Vecteur v(Taille);
	int i=0;
	while (i < Taille) {
		v.T[i] = T[i] * k;
		i++;
	}
	return v;
}

Vecteur operator*(float k, const Vecteur& v) {
	Vecteur vec(v);
	return vec * k;
}

Vecteur& Vecteur::operator=(const Vecteur& v) {
	Vecteur vec(v);
	return vec;
}

bool Vecteur::operator==(const Vecteur& v) {
	if (!TailleEgale(v)) return false;
	int i=0;
	while (i < Taille) {
		if (T[i] != v.T[i]) return false;
		i++;
	}
	return true;
}

bool Vecteur::operator!=(const Veceur& v) {
	return (*this != v);
}

int main(int argc, char** argv) {
	Vecteur a(2), b(2);
	a[0] = 2;
	a[1] = 3;
	b[0] = 1;
	b[1] = 2;
	float p = a * b;
	std::cout << p << std::endl;
	Vecteur c;
	c = a;
	c.Affiche();
	return 0;
}
