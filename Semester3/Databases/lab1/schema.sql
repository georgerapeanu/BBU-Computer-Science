CREATE TABLE USERS (
	id INT NOT NULL,
	name VARCHAR(255) NOT NULL,
	PRIMARY KEY (id)
)


CREATE TABLE POSTS (
	id INT NOT NULL,
	userId INT NOT NULL,
	text VARCHAR(255) NOT NULL,
	PRIMARY KEY (id),
	FOREIGN KEY (userId) REFERENCES USERS(id)
)

CREATE TABLE COMMENTS (
	id INT NOT NULL,
	postId INT NOT NULL,
	userId INT NOT NULL,
	text VARCHAR(255) NOT NULL,
	PRIMARY KEY (id),
	FOREIGN KEY (postId) REFERENCES POSTS(id),
	FOREIGN KEY (userId) REFERENCES USERS(id)
)

CREATE TABLE USER_COMMENT_LIKES (
	userId INT NOT NULL,
	commentId INT NOT NULL,
	PRIMARY KEY(userId, commentId),
	FOREIGN KEY (userId) REFERENCES USERS(id),
	FOREIGN KEY (commentId) REFERENCES COMMENTS(id)
)

CREATE TABLE USER_POST_LIKES (
	userId INT NOT NULL,
	postId INT NOT NULL,
	PRIMARY KEY(userId, postId),
	FOREIGN KEY (userId) REFERENCES USERS(id),
	FOREIGN KEY (postId) REFERENCES POSTS(id)
)

CREATE TABLE STORIES (
	id INT NOT NULL,
	userId INT NOT NULL,
	contentLink VARCHAR(255) NOT NULL,
	PRIMARY KEY (id),
	FOREIGN KEY (userId) REFERENCES USERS(id)
)

CREATE TABLE CATEGORIES (
	name VARCHAR(255) NOT NULL,
	PRIMARY KEY (name)
)

CREATE TABLE CATEGORY_POST (
	categoryName VARCHAR(255) NOT NULL,
	postId INT NOT NULL,
	PRIMARY KEY(categoryName, postId),
	FOREIGN KEY (categoryName) REFERENCES CATEGORIES(name),
	FOREIGN KEY (postId) REFERENCES POSTS(id)
)

CREATE TABLE CONNECTIONS (
	firstUserId INT NOT NULL,
	secondUserId INT NOT NULL,
	PRIMARY KEY(firstUserId, secondUserId),
	FOREIGN KEY (firstUserId) REFERENCES USERS(id),
	FOREIGN KEY (secondUserId) REFERENCES USERS(id)
)

CREATE TABLE PRIVILEDGES (
	id INT NOT NULL,
	isAdmin BIT NOT NULL,
	isModerator BIT NOT NULL,
	PRIMARY KEY (id),
	FOREIGN KEY (id) REFERENCES USERS(id)
)