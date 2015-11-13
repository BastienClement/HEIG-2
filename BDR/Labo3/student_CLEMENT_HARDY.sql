USE sakila;

-- Exercice 01
SELECT 
    title, release_year
FROM
    film
WHERE
    rating = 'G' AND length > 100
        AND replacement_cost = 29.99
ORDER BY title;
-- END Exercice 01

-- Exercice 02
SELECT 
    customer_id, first_name, last_name
FROM
    customer
WHERE
    first_name = 'TRACY' AND store_id = 1
ORDER BY customer_id DESC;
-- END Exercice 02

-- Exercice 03
SELECT 
    customer_id, first_name, last_name
FROM
    customer
INNER JOIN
	address ON address.address_id = customer.address_id
WHERE
    active = 1 AND store_id = 2
        AND city_id = 321
ORDER BY last_name;
-- END Exercice 03

-- Exercice 04
SELECT 
    country, city, postal_code
FROM
    city
INNER JOIN
	country ON country.country_id = city.country_id
INNER JOIN
	address ON address.city_id = city.city_id
WHERE
	country = "France"
	OR (city.city_id > 50 AND city.city_id < 58)
ORDER BY
	country, city, postal_code;
-- END Exercice 04

-- Exercice 05
SELECT DISTINCT
    film.film_id, film.title, language.name AS language
FROM
    film
INNER JOIN
	film_category ON film_category.film_id = film.film_id
INNER JOIN
	category ON category.category_id = film_category.category_id
INNER JOIN
	film_actor ON film_actor.film_id = film.film_id
INNER JOIN
	actor ON film_actor.actor_id = actor.actor_id
INNER JOIN
	language ON language.language_id = film.language_id
WHERE
	category.name = "Sci-Fi"
    AND actor.first_name IN ("BEN", "ALAN")
ORDER BY
	film.film_id DESC;
-- END Exercice 05

-- Exercice 06
SELECT DISTINCT
    cl.customer_id, cl.first_name, cl.last_name, cr.customer_id, cr.first_name, cr.last_name
FROM
    rental AS l
CROSS JOIN
	rental AS r
INNER JOIN
	inventory AS il ON il.inventory_id = l.inventory_id
INNER JOIN
	inventory AS ir ON ir.inventory_id = r.inventory_id
INNER JOIN
	customer AS cl ON cl.customer_id = l.customer_id
INNER JOIN
	customer AS cr ON cr.customer_id = r.customer_id
WHERE
	il.film_id = ir.film_id
    AND l.customer_id != r.customer_id
    AND l.customer_id < r.customer_id;
-- END Exercice 06

-- Exercice 07a
SELECT DISTINCT
    actor.first_name, actor.last_name
FROM
    actor
INNER JOIN
	film_actor ON film_actor.actor_id = actor.actor_id
INNER JOIN
	film_category ON film_category.film_id = film_actor.film_id
INNER JOIN
	category ON category.category_id = film_category.category_id
WHERE
	category.name = "Action"
    AND (actor.first_name LIKE "B%" OR actor.last_name LIKE "A%");
-- END Exercice 07a

-- Exercice 07b
SELECT DISTINCT
    actor.first_name, actor.last_name
FROM
    actor, film_actor, film_category, category
WHERE
	film_actor.actor_id = actor.actor_id
    AND film_category.film_id = film_actor.film_id
    AND category.category_id = film_category.category_id
	AND category.name = "Action"
    AND (actor.first_name LIKE "B%" OR actor.last_name LIKE "A%");
-- END Exercice 07b

-- Exercice 08
SELECT
	first_name, last_name
FROM
	(
		SELECT DISTINCT
			customer.customer_id, customer.first_name, customer.last_name, inventory.film_id
		FROM
			customer
		INNER JOIN
			rental ON rental.customer_id = customer.customer_id
		INNER JOIN
			inventory ON inventory.inventory_id = rental.inventory_id
		INNER JOIN
			film_actor ON film_actor.film_id = inventory.film_id
		INNER JOIN
			actor ON actor.actor_id = film_actor.actor_id
		WHERE
			actor.first_name = "EMILY"
			AND actor.last_name = "DEE"
	) AS X
GROUP BY
	customer_id
HAVING
	COUNT(*) = (
		SELECT
			COUNT(*)
		FROM
			film
		INNER JOIN
			film_actor ON film_actor.film_id = film.film_id
		INNER JOIN
			actor ON actor.actor_id = film_actor.actor_id
		WHERE
			actor.first_name = "EMILY"
			AND actor.last_name = "DEE"
	)
-- END Exercice 08

-- Exercice 09a

-- END Exercice 09a

-- Exercice 09b

-- END Exercice 09b

-- Exercice 10

-- END Exercice 10

-- Exercice 11

-- END Exercice 11

-- Exercice 12

-- END Exercice 12

-- Exercice 13a

-- END Exercice 13a

-- Exercice 13b

-- END Exercice 13b

-- Exercice 14

-- END Exercice 14

-- Exercice 15

-- END Exercice 15

-- Exercice 16

-- END Exercice 16

-- Exercice 17a

-- END Exercice 17a

-- Exercice 17b

-- END Exercice 17b

-- Exercice 17c

-- END Exercice 17c

-- Exercice 18a

-- END Exercice 18a

-- Exercice 18b

-- END Exercice 18b

-- Exercice 18c

-- END Exercice 18c

-- Exercice 19

-- END Exercice 19

-- Exercice 20

-- END Exercice 20

-- Exercice 20d

-- END Exercice 20d
