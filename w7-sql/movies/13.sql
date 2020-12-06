-- list the names of all people who starred in a movie in which Kevin Bacon also starred
-- result 1 col and 176 rows

select name from people 
where id in (
    select distinct(person_id) from stars 
    where movie_id in (
        select movie_id from stars 
        where person_id=(
            select id from people where name="Kevin Bacon" and birth=1958
        )
    )
    and person_id!=(select id from people where name="Kevin Bacon" and birth=1958)
);