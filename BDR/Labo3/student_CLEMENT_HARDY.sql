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
    customer_id as numéro, first_name as prénom, last_name as nom
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
    country as pays, city as ville, postal_code as npa
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
    cl.customer_id as customer1_id, cl.first_name as customer1_first_name, cl.last_name as customer1_last_name, 
	cr.customer_id as customer2_id, cr.first_name as customer2_first_name, cr.last_name as customer2_last_name
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
	customer_id, first_name, last_name
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
	);
-- END Exercice 08

-- Exercice 09a
SELECT 
    title as titre, COUNT(*) AS nombre_acteurs
FROM
    film
INNER JOIN
	film_category ON film.film_id = film_category.film_id
INNER JOIN
	category ON category.category_id = film_category.category_id
INNER JOIN
	film_actor ON film.film_id = film_actor.film_id
WHERE
    name = 'Music'
GROUP BY 
	title
ORDER BY 
	nombre_acteurs DESC;
-- END Exercice 09a

-- Exercice 09b
SELECT 
    title as titre, COUNT(*) AS nombre_acteurs
FROM
    film
INNER JOIN
	film_category ON film.film_id = film_category.film_id
INNER JOIN
	category ON category.category_id = film_category.category_id
INNER JOIN
	film_actor ON film.film_id = film_actor.film_id
WHERE
    name = 'Music'
GROUP BY 
	title
HAVING 
	nombre_acteurs > 7
ORDER BY 
	nombre_acteurs DESC;
-- END Exercice 09b

-- Exercice 10
SELECT 
    category.category_id as id, name as nom, COUNT(*) AS nb_films_associés
FROM
    category
INNER JOIN
    film_category ON film_category.category_id = category.category_id
GROUP BY 
	category.category_id
HAVING 
	nb_films_associés > 60
ORDER BY 
	name;
-- END Exercice 10

-- Exercice 11
SELECT 
	film_id as id_min, title as titre_min, length as durée_min
FROM
	film
WHERE
	length = 
		(
			SELECT
				MIN(length) 
			FROM 
				film
		);
-- END Exercice 11

-- Exercice 12
SELECT
	actor.actor_id, count(*) AS nombre_films
FROM 
	actor
INNER JOIN
	film_actor ON actor.actor_id = film_actor.actor_id
GROUP BY 
	actor_id
HAVING 
	nombre_films > 35;
-- END Exercice 12

-- Exercice 13a
SELECT
	film.film_id as id, title as titre
FROM 
	film
WHERE 
	film.film_id < 100
	AND	film_id IN (
					SELECT 
						film_id
					FROM (    
							SELECT 
								film_id, count(*)
							FROM
								film_actor
							GROUP BY 
								actor_id
							HAVING 
								count(*) > 35
							) AS a
				)
ORDER BY 
	film.film_id;
-- END Exercice 13a

-- Exercice 13b
SELECT 
	film.film_id as id, title as titre
FROM 
	film
INNER JOIN
	(
		SELECT 
			film_id, count(*)
		FROM
			film_actor
		GROUP BY 
			actor_id
		HAVING 
			count(*) > 35
	) as a ON a.film_id = film.film_id
WHERE 
	film.film_id < 100
ORDER BY 
	film.film_id;
-- END Exercice 13b

-- Exercice 14
SELECT
	film_id, title, rental_rate as prix
FROM
	film
WHERE
	film_id NOT IN (
					SELECT DISTINCT
						film_id
					FROM inventory
                    )
	AND rental_rate < 2.00;
-- END Exercice 14

-- Exercice 15
SELECT
	SUM(length)/(16*60) as jours
FROM
	film;
-- END Exercice 15

-- Exercice 16
SELECT
	customer.customer_id as id, last_name as nom, first_name as prénom, country as pays,
	count(inventory.inventory_id) as nombre_films_total, SUM(film.rental_rate) as total_dépense, AVG(film.rental_rate) as dépense_moyenne
FROM
	customer
INNER JOIN
	address ON address.address_id = customer.address_id
INNER JOIN
	city ON city.city_id = address.address_id
INNER JOIN
	country ON country.country_id = city.country_id
INNER JOIN
	rental ON rental.customer_id = customer.customer_id
INNER JOIN
	inventory ON inventory.inventory_id = rental.inventory_id
INNER JOIN
	film ON film.film_id = inventory.film_id
    
WHERE 
	country IN ("India", "Japan", "Morocco")
GROUP BY
	id
HAVING
	dépense_moyenne > 3.4
ORDER BY
	country, last_name;
-- END Exercice 16

-- Exercice 17a
SELECT 
	customer_id as id, last_name as nom, first_name as prénom, country as pays
FROM
	customer
INNER JOIN
	address ON address.address_id = customer.address_id
INNER JOIN
	city ON city.city_id = address.address_id
INNER JOIN
	country ON country.country_id = city.country_id
WHERE 
	country IN ("France", "Japan")
	AND EXISTS (
				SELECT DISTINCT 
					customer_id
				FROM 
					rental
				WHERE
					return_date IS NULL
					AND customer.customer_id = rental.customer_id
				)
ORDER BY
	country, last_name;
-- END Exercice 17a

-- Exercice 17b
SELECT 
	customer_id as id, last_name as nom, first_name as prénom, country as pays
FROM
	customer
INNER JOIN
	address ON address.address_id = customer.address_id
INNER JOIN
	city ON city.city_id = address.address_id
INNER JOIN
	country ON country.country_id = city.country_id
WHERE 
	country IN ("France", "Japan")
    AND customer_id IN (
						SELECT DISTINCT 
							customer_id
						FROM 
							rental
						WHERE
							return_date IS NULL
						)
ORDER BY
	country, last_name;
-- END Exercice 17b

-- Exercice 17c
SELECT
	customer.customer_id as id, last_name as nom, first_name as prénom, country as pays
FROM
	customer
INNER JOIN
	address ON address.address_id = customer.address_id
INNER JOIN
	city ON city.city_id = address.address_id
INNER JOIN
	country ON country.country_id = city.country_id
INNER JOIN
	rental ON rental.customer_id = customer.customer_id
WHERE 
	country IN ("France", "Japan")
    AND return_date IS NULL
GROUP BY
	id
ORDER BY
	country, last_name;
-- END Exercice 17c

-- Exercice 18a
SELECT 
	*
FROM 
	payment
WHERE	
	amount > 11;
-- END Exercice 18a

-- Exercice 18b
DELETE 
FROM
	payment
WHERE
	amount > 11;
-- END Exercice 18b

-- Exercice 18c
SELECT 
	*
FROM 
	payment
WHERE	
	amount > 11;
-- END Exercice 18c

-- Exercice 19
UPDATE 
	payment
SET 
	amount = amount*1.5, last_update = now()
WHERE 
	amount > 5;
-- END Exercice 19

-- Exercice 20
INSERT INTO
	city (city, country_id, last_update)
VALUES
	(
		"Nyon",
		(SELECT country_id FROM country WHERE country = "Switzerland"),
		NOW()
    );
	
INSERT INTO 
	adDress (address, district, city_id, postal_code, phone, last_update)
VALUES
	(
		"Rue du centre", 
		"Vaud",
		(SELECT city_id FROM city ORDER BY city_id DESC LIMIT 1),
		"1260", 
		"022/360.00.00", 
		NOW()
	);
    
INSERT INTO 
	customer (store_id, first_name, last_name, email, address_id, active, create_date)
VALUES
	(
		1,
        "MARCEL",
		"ROCHAT",
        "mr@bluewin.ch",
        (SELECT address_id FROM address ORDER BY address_id DESC LIMIT 1),
        true,
        NOW()
	);
-- END Exercice 20

-- Exercice 20d
SELECT
	customer.customer_id, store_id, first_name, last_name, email, customer.address_id, address, district, postal_code, phone, city.city_id,  city, country
FROM
	customer
INNER JOIN
	address ON address.address_id = customer.address_id
INNER JOIN
	city ON city.city_id = address.city_id
INNER JOIN
	country ON country.country_id = city.country_id

WHERE first_name = "Marcel"
AND last_name = "Rochat";
-- END Exercice 20d
