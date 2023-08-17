#ifndef ABSTRACTPRODUCT_H
#define ABSTRACTPRODUCT_H
// direttive di inclusione
#include <iostream>
#include <string>
#include "IProductVisitor.h"
#include "IConstProductVisitor.h"

// direttive d'uso
using std::cout;
using std::endl;

// classe astratta
class AbstractProduct {
	private:
		unsigned int id; 
		float prezzo;
		std::string nome;
		std::string imagePath;
		std::string description;
	public:
		// costruttore standard e distruttore standard
		AbstractProduct(const unsigned int i, float p, std::string n, std::string path, std::string description);
		virtual ~AbstractProduct();
		// getters e setters
		const unsigned int getId() const; 
		const float& getPrezzo() const; 
		AbstractProduct& setPrezzo(const float& p); 
		const string& getNome() const; 
		AbstractProduct& setNome(const string& n); 
		const std::string& getImagePath() const;
		AbstractProduct& setImagePath(const std::string& path);
		const std::string& getDescription() const;
		AbstractProduct& setDescription(const std::string& des);
		// metodi virtuali puri
		virtual void accept(IProductVisitor* v) = 0;
		virtual void accept(IConstProductVisitor* v) = 0;
};

#endif
