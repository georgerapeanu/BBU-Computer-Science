INSERT INTO USERS(USERS.id, USERS.name) VALUES (1, 'USER1');
INSERT INTO USERS(id, name) VALUES (2, 'USER2');
INSERT INTO USERS(id, name) VALUES (3, 'USER3');
INSERT INTO USERS(id, name) VALUES (4, 'USER4');
INSERT INTO USERS(id, name) VALUES (5, 'USER5');


INSERT INTO POSTS VALUES (1, 1, 'POST1');
INSERT INTO POSTS VALUES (2, 1, 'POST2');
INSERT INTO POSTS VALUES (3, 2, 'POST3');
INSERT INTO POSTS VALUES (4, 5, 'POST4');
-- INSERT INTO POSTS VALUES (2, 7, 'ERROR_POST2');

INSERT INTO COMMENTS VALUES (1, 1, 1, 'COMMENT1');
INSERT INTO COMMENTS VALUES (2, 1, 2, 'COMMENT2');
INSERT INTO COMMENTS VALUES (3, 2, 2, 'COMMENT3');
INSERT INTO COMMENTS VALUES (4, 2, 2, 'COMMENT4');

INSERT INTO CATEGORIES VALUES ('advertisement');
INSERT INTO CATEGORIES VALUES ('news');
INSERT INTO CATEGORIES VALUES ('normal');

INSERT INTO CATEGORY_POST VALUES ('normal', 1);
INSERT INTO CATEGORY_POST VALUES ('normal', 2);
INSERT INTO CATEGORY_POST VALUES ('news', 2);
INSERT INTO CATEGORY_POST VALUES ('advertisement', 4);
INSERT INTO CATEGORY_POST VALUES ('news', 4);

INSERT INTO CONNECTIONS VALUES (1, 2);
INSERT INTO CONNECTIONS VALUES (2, 3);
INSERT INTO CONNECTIONS VALUES (3, 4);
INSERT INTO CONNECTIONS VALUES (4, 5);

INSERT INTO PRIVILEDGES VALUES (1, 1, 1);
INSERT INTO PRIVILEDGES VALUES (2, 0, 1);
INSERT INTO PRIVILEDGES VALUES (3, 0, 1);
INSERT INTO PRIVILEDGES VALUES (4, 0, 0);
INSERT INTO PRIVILEDGES VALUES (5, 0, 0);

INSERT INTO STORIES VALUES (1, 1, 'story1');
INSERT INTO STORIES VALUES (2, 1, 'story2');
INSERT INTO STORIES VALUES (3, 2, 'none');

INSERT INTO USER_POST_LIKES VALUES(1, 1);
INSERT INTO USER_POST_LIKES VALUES(2, 1);
INSERT INTO USER_POST_LIKES VALUES(3, 1);
INSERT INTO USER_POST_LIKES VALUES(4, 1);
INSERT INTO USER_POST_LIKES VALUES(1, 2);
INSERT INTO USER_POST_LIKES VALUES(2, 2);
INSERT INTO USER_POST_LIKES VALUES(1, 3);
INSERT INTO USER_POST_LIKES VALUES(2, 3);
INSERT INTO USER_POST_LIKES VALUES(3, 3);
INSERT INTO USER_POST_LIKES VALUES(4, 2);
INSERT INTO USER_POST_LIKES VALUES(1, 4);

INSERT INTO USER_COMMENT_LIKES VALUES(1, 3);
INSERT INTO USER_COMMENT_LIKES VALUES(2, 3);
INSERT INTO USER_COMMENT_LIKES VALUES(3, 3);
INSERT INTO USER_COMMENT_LIKES VALUES(4, 2);
INSERT INTO USER_COMMENT_LIKES VALUES(1, 4);
INSERT INTO USER_COMMENT_LIKES VALUES(2, 1);



UPDATE USERS 
SET name = 'UPDATE_USER2'
WHERE id = 2 OR id =1;

UPDATE POSTS 
SET text = 'UPDATE_POST1'
WHERE id = 1 AND id = 2;

UPDATE COMMENTS
SET text = 'UPDATED_COMMENT1'
WHERE text LIKE 'COMMENT_';

DELETE 
FROM USER_COMMENT_LIKES 
WHERE userId IN (2);

DELETE
FROM USER_POST_LIKES 
WHERE userId BETWEEN 1 AND 2


------------------------------------------------------------------a. 2 queries with the union operation; use UNION [ALL] and OR;


SElECT userId, postId AS mediaId FROM USER_POST_LIKES upl 
WHERE upl.userId  = 1 OR upl.userId = 2
UNION
SElECT userId, commentId AS mediaId FROM USER_COMMENT_LIKES ucl
WHERE ucl.userId  = 1 OR ucl.userId = 2;

SElECT userId, id AS contentId FROM POSTS p  
WHERE p.userId  = 1 OR p.userId = 2
UNION ALL
SElECT userId, id AS contentId FROM COMMENTS c  
WHERE c.userId  = 1 OR c.userId = 2;


------------------------------------------------------------------b. 2 queries with the intersection operation; use INTERSECT and IN;


SELECT userId FROM POSTS p 
INTERSECT
SELECT userID FROM COMMENTS c
WHERE userId IN (2, 4);

SELECT userId FROM USER_POST_LIKES upl  
INTERSECT
SELECT userID FROM USER_COMMENT_LIKES ucl 
WHERE userId IN (2, 4);


------------------------------------------------------------------c. 2 queries with the difference operation; use EXCEPT and NOT IN;


SELECT userId FROM POSTS p 
WHERE userId NOT IN (1, 1)
EXCEPT
SELECT userID FROM COMMENTS c
WHERE userId NOT IN (1, 1);

SELECT userId FROM USER_POST_LIKES upl
WHERE userId NOT IN (1, 1)
EXCEPT
SELECT userID FROM USER_COMMENT_LIKES ucl 
WHERE userId NOT IN (1, 1);


------------------------------------------------------------------d. 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one query per operator); one query will join at least 3 tables, while another one will join at least two many-to-many relationships;

SELECT u.id, SUM(like_table.likes) as total_likes
FROM USERS u 
INNER JOIN POSTS p 
ON u.id = p.userId 
INNER JOIN (
	SELECT upl.postId as id, COUNT(*) as likes 
	FROM USER_POST_LIKES upl 
	GROUP BY upl.postId) like_table 
ON like_table.id = p.id
GROUP BY u.id;


SELECT *
FROM USERS u
LEFT JOIN POSTS p 
on u.id = p.userId 
LEFT JOIN COMMENTS c 
on p.userId = c.postId 
ORDER BY p.text ASC;

SELECT c.text, u.id 
FROM COMMENTS c
RIGHT JOIN USERS u
on u.id = c.userId
ORDER BY c.text ASC;

SELECT p.id, p.[text] , c.name 
FROM POSTS p
FULL JOIN CATEGORY_POST cp  
ON cp.postId = p.id 
FULL JOIN CATEGORIES c 
on cp.categoryName = c.name;

------------------------------------------------------------------e. 2 queries with the IN operator and a subquery in the WHERE clause; in at least one case, the subquery must include a subquery in its own WHERE clause;
---select all user ids which have at least one like given to a post that isnt theirs

SELECT DISTINCT userId 
FROM USER_POST_LIKES upl 
WHERE upl.postId IN (
	SELECT TOP 1 id 
	FROM POSTS p 
	WHERE upl.postId = p.id AND p.userId <> upl.userId
);

---select all comments of users which have at least one like given to a post that isnt theirs

SELECT id FROM COMMENTS c 
WHERE c.userId IN (
	SELECT DISTINCT userId 
	FROM USER_POST_LIKES upl 
	WHERE upl.postId IN (
		SELECT TOP 1 id 
		FROM POSTS p 
		WHERE upl.postId = p.id AND p.userId <> upl.userId
	)
);

------------------------------------------------------------------f. 2 queries with the EXISTS operator and a subquery in the WHERE clause;
---select all user ids which have at least one like given to a post that isnt theirs

SELECT DISTINCT userId 
FROM USER_POST_LIKES upl 
WHERE EXISTS (
	SELECT TOP 1 id 
	FROM POSTS p 
	WHERE upl.postId = p.id AND p.userId <> upl.userId
);

---select all user ids which have at least one like given to a comment that isnt theirs

SELECT DISTINCT userId 
FROM USER_COMMENT_LIKES ucl
WHERE EXISTS (
	SELECT TOP 1 id 
	FROM COMMENTS c 
	WHERE ucl.commentId = c.id AND c.userId <> ucl.userId
);



------------------------------------------------------------------g. 2 queries with a subquery in the FROM clause;                         

SELECT u.id, t.id as storyId
FROM USERS u INNER JOIN (SELECT * FROM STORIES s WHERE s.contentLink LIKE  '_one') t
ON t.userId = u.id;

SELECT u.id, SUM(like_table.likes) as total_likes
FROM USERS u 
INNER JOIN POSTS p 
ON u.id = p.userId 
INNER JOIN (
	SELECT upl.postId as id, COUNT(*) as likes 
	FROM USER_POST_LIKES upl 
	GROUP BY upl.postId) like_table 
ON like_table.id = p.id
GROUP BY u.id;



------------------------------------------------------------------h. 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 2 of the latter will also have a subquery in the HAVING clause; use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;

SELECT upl.postId, COUNT(*)
FROM USER_POST_LIKES upl 
GROUP BY upl.postId;

SELECT upl.postId, COUNT(*) as likes 
FROM USER_POST_LIKES upl 
GROUP BY upl.postId
HAVING COUNT(*) > 2;

--select all posts whith positive likes and at least 2 categories
SELECT upl.postId, COUNT(*) as likes
FROM USER_POST_LIKES upl 
GROUP BY upl.postId
HAVING COUNT(*) > 0 AND upl.postId in (
	SELECT cp.postId
	FROM CATEGORY_POST cp 
	GROUP BY cp.postId  
	HAVING COUNT(*) > 1
);

-- select all stories of friends and count them for a given user
SELECT s.userId, COUNT(*)
FROM STORIES s
GROUP BY s.userId  
HAVING s.userId in (
	SELECT DISTINCT  c.secondUserId 
	FROM CONNECTIONS c 
	WHERE 2 = c.firstUserId 
	UNION 
	SELECT DISTINCT  c.firstUserId 
	FROM CONNECTIONS c 
	WHERE 2 = c.secondUserId 
)



------------------------------------------------------------------i. 4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator); rewrite 2 of them with aggregation operators, and the other 2 with IN / [NOT] IN.

SELECT id
FROM USERS u
WHERE id = ANY (SELECT DISTINCT userId FROM POSTS p);
--- WHERE id IN (SELECT DISTINCT userId FROM POSTS p);


SELECT id
FROM USERS u
WHERE id <> ALL (SELECT DISTINCT userId FROM POSTS p);
--- WHERE id NOT IN (SELECT DISTINCT userId FROM POSTS p);



SELECT upl.postId  as likes 
FROM USER_POST_LIKES upl 
GROUP BY upl.postId
HAVING COUNT(*) >= ALL(
	SELECT COUNT(*) as likes 
	FROM USER_POST_LIKES upl2 
	GROUP BY upl2.postId
)
--- HAVING COUNT() >= MAX

SELECT upl.postId  as likes 
FROM USER_POST_LIKES upl 
GROUP BY upl.postId
HAVING COUNT(*) > ANY(
	SELECT COUNT(*) as likes 
	FROM USER_POST_LIKES upl2 
	GROUP BY upl2.postId
)
--- HAVING COUNT > MIN()

------------------------------------------------------------------

SELECT COALESCE(comment_likes_table.id, post_likes_table.id) AS userId, (ISNULL(comment_likes_table.comment_likes, 0) + ISNULL(post_likes_table.post_likes, 0)) AS total_likes
FROM (
	SELECT ucl.userId as id, COUNT(ucl.userId) AS comment_likes
	FROM USER_COMMENT_LIKES ucl 
	GROUP BY ucl.userId 
) comment_likes_table
FULL JOIN (
	SELECT upl.userId as id, COUNT(upl.userId) AS post_likes
	FROM USER_POST_LIKES upl
	GROUP BY upl.userId 
) post_likes_table
ON comment_likes_table.id=post_likes_table.id;

SELECT COALESCE(count_comments_table.id, count_posts_table.id) AS userId, (ISNULL(count_posts_table.count_posts, 0) + ISNULL(count_comments_table.count_comments, 0)) AS total_media
FROM (
	SELECT p.userId as id, COUNT(*) as count_posts
	FROM POSTS p 
	GROUP BY p.userId
) count_posts_table
FULL JOIN (
	SELECT c.userId as id, COUNT(*) as count_comments
	FROM COMMENTS c 
	GROUP BY c.userId
) count_comments_table
ON count_posts_table.id = count_comments_table.id;

SELECT post_category_likes_table.category_name, (CONVERT(float, SUM(post_category_likes_table.likes)) / COUNT(*)) AS average_likes_per_category
FROM (
	SELECT cp.categoryName AS category_name, like_table.likes AS likes
	FROM CATEGORY_POST cp 	
	INNER JOIN (
		SELECT upl.postId AS postId, COUNT(*) AS likes
		FROM USER_POST_LIKES upl 
		GROUP BY upl.postId 
	) like_table
	ON cp.postId = like_table.postId
) post_category_likes_table
GROUP BY post_category_likes_table.category_name;

