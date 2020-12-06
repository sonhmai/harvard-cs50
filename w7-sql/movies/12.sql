-- list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred
-- result 1 col 6 rows

select title from movies 
where id in (
    select b.movie_id from (
        select movie_id from stars
        where person_id=(select id from people where name='Johnny Depp')
    ) b
    join (
        select movie_id from stars
        where person_id=(select id from people where name='Helena Bonham Carter')
    ) t on t.movie_id=b.movie_id
);
