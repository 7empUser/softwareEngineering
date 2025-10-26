#include <iostream>
#include <vector>
#include <cstdint>

class Item {
public:
	virtual ~Item() = default;
	virtual float getPrice() const = 0;
};

class Product : public Item {
private:
	float price;
public:
	Product(float _price) : price(_price) {}

	float getPrice() const override {
		return price;
	}
};

class Box : public Item {
private:
	std::vector<Item*> children;
public:
	void addChild(Item& _item) {
		children.push_back(&_item);
	}

	float getPrice() const override {
		float totalPrice = 0.0f;
		for (const auto& child : children) {
			totalPrice += child->getPrice();
		}
		return totalPrice;
	}
};

int main() {
	setlocale(LC_ALL, "Russian");


	Box mainBox;
	Box secondBox;

	Product phone = Product(15);
	Product headphones(5);
	Product charger(3);

	secondBox.addChild(phone);
	secondBox.addChild(headphones);
	mainBox.addChild(secondBox);
	mainBox.addChild(charger);

	std::cout << "Стоимость второй коробки(phone && headphones): " << secondBox.getPrice() << std::endl;
	std::cout << "Стоимость главной коробки(phone && headphones && charger): " << mainBox.getPrice() << std::endl;

	return 0;
}