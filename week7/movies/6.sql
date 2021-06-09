SELECT AVG(rating) 
FROM ratings 
WHERE movie_id IN 
(SELECT id year 
FROM movies 
WHERE year > 2011);