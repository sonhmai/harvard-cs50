-- list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Chadwick Boseman.
-- result 1 col 5 rows
with _movies as (
    select movie_id as id from stars
    where person_id=(select id from people where name="Chadwick Boseman")
)
select title from movies 
where id in (
    select movie_id from ratings
    join _movies on ratings.movie_id=_movies.id
    order by rating desc
    limit 5
)
