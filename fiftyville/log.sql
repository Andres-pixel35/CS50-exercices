-- Keep a log of any SQL queries you execute as you solve the mystery.
-- well, the first query was;
SELECT * FROM crime_scene_reports WHERE description LIKE '%duck%';
-- I thought the crime description would mention duck and it did, so i know that to look for know, bakery

-- the second query was:
SELECT * FROM interviews WHERE transcript LIKE '%bakery%';
-- that gave me 4 witnesses, but with thanks for the month i know who I must rule out.
-- they give interesting infromation about who are they and where they went, so know it's time to check that.

-- the third query was;
SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28 AND activity == 'exit'
AND minute >= 15 AND minute <=25 AND hour = 10;
-- thanks of ruth i knew the thief left within ten minutes after the theft, so now i know the license of any car
-- that left within those ten minutes

-- the fourth query was;
SELECT * FROM atm_transactions WHERE month = 7 AND day = 28
AND atm_location == 'Leggett Street' AND transaction_type == 'withdraw';
-- thanks to eugene i knew the thief withdraw some money and where. someone from them must be the thief.

-- the fifth query was;
SELECT * FROM phone_calls WHERE day = 28 AND duration < 60;
-- thanks for the last witness i know the duration of the call, so i can filter.
-- now i have information about them, it's time to link data.

--the sixth query was;
SELECT * FROM flights WHERE day = 29;
-- with this information and the next i should be able to determinate to which city they went
-- as i know the took the earliest flight to another city.

-- the seventh query was;
SELECT * FROM airports WHERE id ==
(SELECT destination_airport_id FROM flights WHERE day = 29 AND hour = 8);
-- knowing that the earliest flight to another city that day was at 8,
-- i can determinate the name of the city and the aiport they went (New York City). now i need names.

-- the eighth query was;
SELECT passport_number FROM passengers WHERE flight_id ==
(SELECT id FROM flights WHERE day = 29 AND hour = 8);
-- with this i know the passport from the people who took the flight to new york that day.
-- more informartion, closer to the thief.

-- the nineth query was;
SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number  FROM atm_transactions WHERE month = 7 AND day = 28
AND atm_location == 'Leggett Street' AND transaction_type == 'withdraw');
-- i have a range of ids, let's see what can i do with that.

-- the tenth query was;
SELECT name FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number  FROM atm_transactions WHERE month = 7 AND day = 28
AND atm_location == 'Leggett Street' AND transaction_type == 'withdraw'))
AND phone_number IN (SELECT caller FROM phone_calls WHERE day = 28 AND duration < 60)
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id ==
(SELECT id FROM flights WHERE day = 29 AND hour = 8))
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND activity == 'exit'
AND minute >= 15 AND minute <=25 AND hour = 10);
-- with all the information reunited i could determinated the thief's name and it's: Bruce.

-- the eleventh query was:
SELECT phone_number FROM people WHERE name == 'Bruce';
-- with this i can make a relation between the caller and the receiver and get the name of the accomplice.

-- the twelfth query was;
SELECT receiver FROM phone_calls WHERE caller ==
(SELECT phone_number FROM people WHERE name == 'Bruce')
AND month = 7 AND day = 28 AND duration < 60;
-- and with this i have the number of the accomplice.

-- the thirteenth query was;
SELECT name FROM people WHERE phone_number ==
(SELECT receiver FROM phone_calls WHERE caller ==
(SELECT phone_number FROM people WHERE name == 'Bruce')
AND month = 7 AND day = 28 AND duration < 60);
-- and finally i have got the name of the accomplice; Robin.
