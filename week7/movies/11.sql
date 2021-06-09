SELECT title
FROM movies as m
INNER JOIN ratings AS r
ON m.id = r.movie_id
INNER JOIN stars AS s
ON r. movie_id = s.movie_id
INNER JOIN people AS p
ON s.person_id = p.id
WHERE p.id IN
(SELECT id
FROM people
WHERE name = "Chadwick Boseman")
ORDER BY r.rating
LIMIT 5;