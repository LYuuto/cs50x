SELECT title FROM movies
WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id from people WHERE name = "Johnny Depp"))
INTERSECT
SELECT title FROM movies
WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id from people WHERE name = "Helena Bonham Carter"));