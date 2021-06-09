SELECT DISTINCT(p.name)
FROM people as p
INNER JOIN stars as s
ON p.id = s.person_id
INNER JOIN movies AS m
ON s.movie_id = m.id
WHERE m.id in
(SELECT DISTINCT(m.id)
FROM movies AS m
INNER JOIN stars as s
ON m.id = s.movie_id
INNER JOIN people as p
ON s.person_id = p.id
WHERE p.name = "Kevin Bacon"
AND p.birth = 1958)
AND p.name != "Kevin Bacon";

/*
To remove Kevin bacon used:
https://stackoverflow.com/questions/60731243/cs50-pset-7-13-sql-i-cant-solve-it-nested-sqlite3-database
*/