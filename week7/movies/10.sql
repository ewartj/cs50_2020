SELECT p.name
FROM people AS p
INNER JOIN directors as d
ON p.id = d.person_id
INNER JOIN ratings  as r
ON d.movie_id = r.movie_id
WHERE r.movie_id IN
(SELECT movie_id
FROM ratings
WHERE rating >= 9.0);
