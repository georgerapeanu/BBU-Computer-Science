CREATE TABLE CoffeeShops(
	id INT IDENTITY PRIMARY KEY,
	name VARCHAR(255),
	startupYear INT,
);

CREATE TABLE Coffees(
	id INT IDENTITY PRIMARY KEY,
	name VARCHAR(255),
	weight INT,
	isAvailable BIT,
	brandId INT,
	price INT,
	coffeeShopId INT
);

CREATE TABLE Ingredients(
	id INT IDENTITY PRIMARY KEY,
	name VARCHAR(255),
	availableQuantity INT
);

CREATE TABLE Brands(
	id INT IDENTITY PRIMARY KEY,
	name VARCHAR(255),
	startYear INT,
	stars INT
);

CREATE TABLE CoffeeIngredient(
	coffeeId INT,
	ingredientId INT,
	requiredQuantity INT,
	
	PRIMARY KEY (coffeeId, ingredientId)
);

ALTER TABLE Coffees ADD CONSTRAINT FK_Coffee_Brand FOREIGN KEY (brandId) REFERENCES Brands(id);
ALTER TABLE Coffees ADD CONSTRAINT FK_Coffee_CoffeeShop FOREIGN KEY (coffeeShopId) REFERENCES CoffeeShops(id);
ALTER TABLE CoffeeIngredient ADD CONSTRAINT FK_CoffeeIngredient_Coffee FOREIGN KEY (coffeeId) REFERENCES Coffees(id);
ALTER TABLE CoffeeIngredient ADD CONSTRAINT FK_CoffeeIngredient_Ingredient FOREIGN KEY (ingredientId) REFERENCES Ingredients(id);
