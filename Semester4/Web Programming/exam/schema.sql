CREATE TABLE Users(
                      id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
                      username VARCHAR(255)
);

CREATE TABLE FamilyRelations(
                                id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
                                userId INT NOT NULL,
                                mother VARCHAR(255),
                                father VARCHAR(255)
);

ALTER TABLE FamilyRelations
    ADD CONSTRAINT FK_Family_Userid FOREIGN KEY (userId) REFERENCES Users(id);