SELECT m.titLe, r.rating 
FROM movies AS m 
LEFT JOIN ratings AS r 
ON id = movie_id 
WHERE year == 2010 AND r.rating IS NOT NULL 
ORDER BY rating 
DESC, m.title DESC;
/*
https://stackoverflow.com/questions/12782676/how-to-order-by-column-if-equal-order-by-another
*/
