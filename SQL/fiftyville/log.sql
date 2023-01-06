-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description FROM crime_scene_reports WHERE id=295;
SELECT name, transcript FROM interviews WHERE day=28 AND month=7 AND year=2021;


-------1. Query given on most information of the interviews------
SELECT Distinct people.name
FROM people
JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate

JOIN bank_accounts
ON bank_accounts.person_id = people.id

JOIN atm_transactions
ON atm_transactions.account_number = bank_accounts.account_number

JOIN phone_calls
ON phone_calls.caller = people.phone_number

JOIN passengers
ON passengers.passport_number = people.passport_number

JOIN flights
ON flights.id = passengers.flight_id

JOIN airports
ON airports.id = flights.origin_airport_id

WHERE bakery_security_logs.year=2021 AND bakery_security_logs.month=7 AND bakery_security_logs.day=28 AND bakery_security_logs.minute >= 15 AND bakery_security_logs.minute <= 25 AND bakery_security_logs.hour=10
AND atm_transactions.year=2021 AND atm_transactions.month=7 AND atm_transactions.day=28 AND atm_location ="Leggett Street" AND transaction_type = 'withdraw'
AND phone_calls.year=2021 AND phone_calls.month=7 AND phone_calls.day=28 AND phone_calls.duration<60
AND flights.year=2021 AND flights.month=7 AND flights.day=29 AND airports.city="Fiftyville"
GROUP BY flights.hour
HAVING MIN(flights.hour);

---It can only be Diana or Bruce the thief!



--Finding out receiver phone number Bruce and Diana to check if their call receiver flew with them
SELECT phone_calls.receiver
FROM phone_calls
JOIN people
ON phone_calls.caller = people.phone_number
WHERE people.name ="Bruce" AND phone_calls.year=2021 AND phone_calls.month=7 AND phone_calls.day=28 AND phone_calls.duration<60;

--Check who Bruce called
SELECT people.name
FROM people
WHERE phone_number="(375) 555-8161";
--Bruce called Robin

--Check if Robin flew with Bruce by getting his flight id first
SELECT flights.id
FROM flights
JOIN airports
ON airports.id = flights.origin_airport_id
JOIN passengers
ON passengers.flight_id = flights.id
JOIN people
ON people.passport_number = passengers.passport_number
WHERE flights.year=2021 AND flights.month=7 AND flights.day=29 AND airports.city="Fiftyville" AND people.name ="Bruce"
GROUP BY flights.hour
HAVING MIN(flights.hour);
--flight id is 36

--Querying if Robin was on flight with id 36
SELECT flights.id
FROM flights
JOIN airports
ON airports.id = flights.origin_airport_id
JOIN passengers
ON passengers.flight_id = flights.id
JOIN people
ON people.passport_number = passengers.passport_number
WHERE flights.year=2021 AND flights.month=7 AND flights.day=29 AND airports.city="Fiftyville" AND people.name ="Robin"
GROUP BY flights.hour
HAVING MIN(flights.hour);
--yes he was



---------------------------------
--Checking who Diana called with same procedure
SELECT phone_calls.receiver
FROM phone_calls
JOIN people
ON phone_calls.caller = people.phone_number
WHERE people.name ="Diana" AND phone_calls.year=2021 AND phone_calls.month=7 AND phone_calls.day=28 AND phone_calls.duration<60;

SELECT people.name
FROM people
WHERE phone_number="(725) 555-3243";

--Check if Philip flew with Diana
SELECT flights.id
FROM flights
JOIN airports
ON airports.id = flights.origin_airport_id
JOIN passengers
ON passengers.flight_id = flights.id
JOIN people
ON people.passport_number = passengers.passport_number
WHERE flights.year=2021 AND flights.month=7 AND flights.day=29 AND airports.city="Fiftyville" AND people.name ="Philip"
GROUP BY flights.hour
HAVING MIN(flights.hour);
--He did not fly with Diana so Bruce is the thief and Robin his accomplice

--Checking where Bruce and Robin flew
SELECT airports.city
FROM airports
JOIN flights
ON airports.id = flights.destination_airport_id
WHERE flights.id=36;
--Bruce and Robin flew to NYC
