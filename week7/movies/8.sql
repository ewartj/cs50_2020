SELECT p.name
FROM people AS p
INNER JOIN stars as s
ON p.id = s.person_id
INNER JOIN movies AS m
ON s.movie_id = m.id
WHERE m.id
IN (SELECT id
FROM movies
WHERE title == "Toy Story");