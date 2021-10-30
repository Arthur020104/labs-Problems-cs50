SELECT title FROM movies, ratings WHERE (id, movie_id) IN (SELECT movie_id,movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Chadwick Boseman"))
ORDER BY(rating)DESC LIMIT 5;