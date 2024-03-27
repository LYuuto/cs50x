-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28;
-- Three witness, mention bakery. id = 295, at 10:15am

SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;
-- 161 10 min of theft, car mot leaving for some time
-- 162 ATM on Legget Street, morning, withdraw
-- 163 earliest fight out on july 29\
SELECT transcript FROM interviews WHERE id = 161 or id = 162 or id = 163;

-- According to 161
SELECT * FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 20 AND activity = "exit";

SELECT license_plate FROM bakery_security_logs WHERE id >= 260 and id <= 264;

SELECT * FROM people
 WHERE license_plate
    IN (SELECT license_plate FROM bakery_security_logs WHERE id >= 260 and id <= 264);
-- five sus

-- According to 162
SELECT * FROM atm_transactions
WHERE year = 2021 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street";

SELECT account_number FROM atm_transactions
WHERE id = 246 or id = 264 or id = 266 or id = 267 or id = 269 or id = 288 or id = 313 or id = 336;
-- 8 sus

SELECT * FROM bank_accounts
WHERE account_number
   IN (SELECT account_number FROM atm_transactions
        WHERE id = 246 or id = 264 or id = 266 or id = 267 or id = 269 or id = 288 or id = 313 or id = 336);

-- person_id of 8 sus people
SELECT person_id FROM bank_accounts
WHERE account_number
   IN (SELECT account_number FROM atm_transactions
        WHERE id = 246 or id = 264 or id = 266 or id = 267 or id = 269 or id = 288 or id = 313 or id = 336);

-- According to 163
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60;
-- 10 sus

-- combining 161 and 162
SELECT id FROM people
 WHERE license_plate
    IN (SELECT license_plate FROM bakery_security_logs WHERE id >= 260 and id <= 264)
INTERSECT
SELECT person_id FROM bank_accounts
 WHERE account_number
   IN (SELECT account_number FROM atm_transactions
        WHERE id = 246 or id = 264 or id = 266 or id = 267 or id = 269 or id = 288 or id = 313 or id = 336);

-- 2 suspect
SELECT * FROM people where id = 467400 or id = 686048;

-- combining with 163
SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60
INTERSECT
SELECT phone_number FROM people where id = 467400 or id = 686048;

SELECT * FROM people WHERE phone_number = "(367) 555-5533";
-- suspected Bruce id = 686048
SELECT * FROM people WHERE id = 686048;

-- accomplice
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60 AND caller = "(367) 555-5533";
-- call history id = 233
SELECT receiver FROM phone_calls WHERE id = 233;

SELECT * FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE id = 233);
-- robin id = 864400

-- where they escape
SELECT * FROM airports WHERE city = "Fiftyville";

SELECT * FROM flights WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29 AND hour <= 12;

SELECT * FROM flights WHERE id = 23 or id = 36 or id = 43;

SELECT * FROM passengers
  JOIN people
    ON passengers.passport_number = people.passport_number
 WHERE people.id = 686048;

SELECT * FROM flights WHERE id = 36;

SELECT * FROM airports WHERE id = 4;
