SELECT m.title
FROM movies AS m
INNER JOIN stars as s
ON m.id = s.movie_id
INNER JOIN people as p
ON s.person_id = p.id
WHERE p.name == "Johnny Depp"
AND m.id IN
(SELECT m.id
FROM movies AS m
INNER JOIN stars as s
ON m.id = s.movie_id
INNER JOIN people as p
ON s.person_id = p.id
WHERE p.name == "Helena Bonham Carter");
