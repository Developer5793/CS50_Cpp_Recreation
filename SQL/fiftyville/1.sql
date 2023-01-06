SELECT title FROM movies WHERE year=2008;


SELECT description FROM crime_scene_reports WHERE id=295;
CREATE TABLE SuspectsAtBakery AS SELECT * license_plate, id FROM bakery_security_logs WHERE month=7 AND day=28 AND hour=10 AND minute IN(11,12,13,14,15,16,17,18,19,20,21,22,23,24,25));
SELECT name, transcript FROM interviews WHERE day=28 AND month=7 AND year=2021;


SELECT people.name
FROM people
JOIN SuspectsAtBakery
ON people.license_plate = SuspectsAtBakery.license_plate

JOIN bank_accounts
ON bank_accounts.person_id = SuspectsAtBakery.id

JOIN atm_transactions
ON atm_tranasactions.account_number = bank_accounts.account_number
WHERE year=2021 AND month=7 AND day=28;
