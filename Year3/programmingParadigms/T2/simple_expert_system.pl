% medical knowledge base

illness("common cold", 0.10, [symptom("blocked nose", 0.98, 0.60), symptom("runny nose", 0.98, 0.60), symptom("sore throat", 0.30, 0.05), symptom("headaches", 0.10, 0.02), symptom("body aches", 0.05, 0.01),
                      symptom("cough", 0.55, 0.45), symptom("sneezing", 0.95, 0.30), symptom("temperature", 0.85, 0.50), symptom("pressure", 0.25, 0.05), symptom("loss of taste and smell", 0.60, 0.25)]).

illness("flu", 0.10, [symptom("temperature", 0.95, 0.70), symptom("body aches", 0.40, 0.10), symptom("exhaustion", 0.92, 0.85), symptom("dry cough", 0.98, 0.90),
              symptom("sore throat", 0.45, 0.25), symptom("headaches", 0.48, 0.05), symptom("difficulty sleeping", 0.75, 0.001), symptom("loss of appetite", 0.50, 0.30), symptom("diarrhoea", 0.36, 0.05), 
              symptom("stomach pain", 0.53, 0.28), symptom("sickness", 0.80, 0.80), symptom("sudden symptoms", 0.98, 0.95)]).

illness("coronavirus", 0.10, [symptom("temperature", 0.95, 0.80), symptom("cough", 0.98, 0.95), symptom("loss of taste and smell", 0.95, 0.30), 
                      symptom("shortness of breath", 0.98, 0.50), symptom("exhaustion", 0.77, 0.20), symptom("sickness", 0.70, 0.25), symptom("body aches", 0.29, 0.06), 
                      symptom("headaches", 0.60, 0.01), symptom("sore throat", 0.75, 0.30), symptom("blocked nose", 0.80, 0.55), 
                      symptom("runny nose", 0.85, 0.75), symptom("loss of appetite", 0.20, 0.01), symptom("diarrhoea", 0.30, 0.03)]).

% Answers to questions that the user could ask
% https://www.nhs.uk/conditions/common-cold/
what_to_do("cold", "Rest and sleep, Drink plenty of water, Gargle salt water to soothe a sore throat, humidify the air and avoid antibiotics and smoking.").

% https://www.nhs.uk/conditions/flu/
what_to_do("flu", "Rest and sleep, keep warm, take paracetamol or ibuprofen, drink plenty of water. If you're in a high risk group or very sick, contact your health care provider.").

% https://www.nhs.uk/conditions/coronavirus‑covid‑19/symptoms/main‑symptoms/
what_to_do("coronavirus", "Get lots of rest, drink plenty of fluids, avoid lying on your back if you have a cough, keep your room cool if you are feeling breathless. Ask for an urgent GP appointment if your symptoms are getting worse or are not getting better.").

% https://www.mayoclinic.org/diseases-conditions/common-cold/symptoms-causes/syc-20351605
risk_factors("cold", "Infants and young children, smokers and those with weakened immune systems are at higher risk of getting a cold.").

% https://www.lung.org/lung-health-diseases/lung-disease-lookup/influenza/symptoms-causes-and-risk
risk_factors("flu", "You are at higher risk of serious illness from influenza if you have a chronic lung or kidney disease, heart disease, diabetes, severe anemia or are immunocompromised.").

% https://www.cdc.gov/coronavirus/2019-ncov/need-extra-precautions/people-with-medical-conditions.html
risk_factors("coronavirus", "People with cancer, chronic kidney, liver and lung diseases, people who are immunocompromised, have heart conditions, or diabetes, are more likely to end up with a severe case of COVID-19.").

prevent_spreading("cold", "To prevent the spreading of common cold, you should wash your hands, disinfect things you touch, cover your cough, stay out of crowds and avoid sharing utensils.").

% https://www.nhsinform.scot/illnesses-and-conditions/infections-and-poisoning/flu
prevent_spreading("flu", "To prevent the spreading of the flu, you should regularly clean surfaces you frequently touch to get rid of germs, use tissues to cover your mouth and nose when you cough or sneeze and put used tissues in a bin as soon as possible.").
prevent_spreading("coronavirus", "To prevent spreading coronavirus, you should get vaccinated against COVID-19, wash your hands throughout the day with soap and water, cover your mouth and nose when you cough or sneeze, regularly clean surfaces you touch often and think about wearing a face covering that fits snugly against your face and has more than 1 layer if you're in close contact with other people, or in crowded places.").

common_symptoms("cold", "Some common symptoms of common cold are having a blocked or runny nose, sore throat, headaches, body aches, a cough, sneezing, high temperature, pressure in your ears and face and loss of taste and smell.").
common_symptoms("flu", "Some common symptoms of the flu are having a high temperature, body aches, exhaustion, a dry cough, sore throat, headaches, difficultysleeping, loss of appetite, diarrhoea, stomach pain, sickness, usually very suddenly.").
common_symptoms("coronavirus", "Some common symptoms of coronavirus are a high temperature, coughing, loss of taste and smell, shortness of breath, exhaustion, sickness, body aches, headaches, sore throat, blocked or runny nose, loss of appetite and diarrhoea.").

% https://www.cdc.gov/flu/symptoms/coldflu.htm
differences("common cold", "flu", "The symptoms of flu can include fever or feeling feverish/chills, cough, sore throat, runny or stuffy nose, muscle or body aches, headaches, and fatigue (tiredness). Cold symptoms are usually milder than the symptoms of flu. People with colds are more likely to have a runny or stuffy nose. Colds generally do not result in serious health problems.").

% https://www.mayoclinic.org/diseases-conditions/coronavirus/in-depth/covid-19-cold-flu-and-allergies-differences/art-20503981
differences("common cold", "coronavirus", "COVID-19 symptoms usually start 2 to 14 days after exposure to SARS-CoV-2. But symptoms of a common cold usually appear 1 to 3 days after exposure to a cold-causing virus. There's no cure for the common cold. Treatment may include pain relievers and cold remedies available without a prescription, such as decongestants. Unlike COVID-19, a cold is usually harmless. Most people recover from a common cold in 3 to 10 days. But some colds may last as long as two or three weeks.").

% https://www.cdc.gov/flu/symptoms/flu-vs-covid19.htm
differences("coronavirus", "flu", "Compared with flu, COVID-19 can cause more severe illness in some people. Compared to people with flu, people infected with COVID-19 may take longer to show symptoms and may be contagious for longer periods of time. You cannot tell the difference between flu and COVID-19 by the symptoms alone because they have some of the same signs and symptoms.  Specific testing is needed to tell what the illness is and to confirm a diagnosis.").


% rules for diagnosis with help from "D. Crookes ‑ An application in Medicine"

% Capture user input in a comma separated manner as a list for diagnosis
observe(L) :-
  write("Please list all your symptoms."), nl,
  read_string(user_input, '\n', '', _, Symptoms),
  split_string(Symptoms, ",", "", L).

diagnose() :-
  patient_could_have(Illness, Probability).

% Start of function to get the most likely illness from a list of lists
find_max(L, O) :-
  maximum(L, 0, [], O).

% Base case for finding most likely illness, returns illness and its probability in list
maximum([], O, L, L).

% Check if probability in current head value of input list is higher than existing probability
maximum([[I|P]|T], M, L, O) :-
  (I > M -> maximum(T, I, [I|P], O);
   maximum(T, M, L, O)).

% Start and end of diagnosis calculation, including results of calculation 
diagnosis :- 
  findall([Probability, Illness], patient_could_have(Illness, Probability), List),
  find_max(List, O),
  (nth0(0, O, P), P > 0.9, nth0(1, O, I), format("You have the ~w!", I), nl, write("Anything else?"), nl, parse_question;
  nth0(0, O, P), P > 0.84, nth0(1, O, I), format("It is very likely that you have the ~w!", I), nl, write("Anything else?"), nl, parse_question;
  nth0(0, O, P), P > 0.49, nth0(1, O, I), format("It is likely that you have the ~w!", I), nl, write("Anything else?"), nl, parse_question;
  nth0(0, O, P), P > 0.1, nth0(1, O, I), format("It is possible that you have the ~w!", I), nl, write("Anything else?"), nl, parse_question;
  write("You do not have the common cold, coronavirus or influenza!"), nl, write("Anything else?"), nl, parse_question).

% Main calculation function to call rest and check if  resulting probability is reasonable
patient_could_have(Illness, Probability) :-
  observe(L),
  illness(Illness, _, _),
  probability(Illness,  Probability, L),
  reasonable(Probability).

% Check if probability is higher than 0.1
reasonable(Probability) :- 
  Probability >= 0.1.

% Go through illnesses and check symptoms to determine probability
probability(Illness, Probability, L) :-
  illness(Illness, P_current, Symptom_list), 
  new_probability(P_current, Symptom_list, Probability, L).

% Base case for probability for if symptoms for illness have all been checked
new_probability(P, [], P, L).

new_probability(P_current, [Symptom | Tail], P_new, L) :-
  update(P_current, Symptom, P_updated, L),
  new_probability(P_updated, Tail, P_new, L).

% Base case for if symptom is in list
member(Symptom_name, [Symptom_name|_]).

% Check if symptom is in list recursively
member(Symptom_name, [_|Tail]) :-
  member(Symptom_name, Tail).

% Update probability if symptom of illness is listed in users list of symptoms
update(P_current, symptom(Symptom_name, Py, Pn), P_new, L) :-
  member(Symptom_name, L),
  bayes(P_current, Py, Pn, P_new).

% Update probability if symptom of illness is not listed in users list of symptoms
update(P_current, symptom(Symptom_name, Py, Pn), P_new, L) :-
  not(member(Symptom_name, L)),
  P1 is 1 - Py,
  P2 is 1 - Pn,
  bayes(P_current, P1, P2, P_new).

% Calculate probability using Bayes theorem
bayes(P, Py, Pn, Pdash) :-
  Top is 1 * Py * P,
  Bottom is (Py * P) + (Pn * (1 - P)),
  Pdash is Top / Bottom.

% Rules to answer user queries

% Base case, where the head of a list is the only element remaining
last_word(Head, [Head]).

% Recursively get last element in list
last_word(Head, [_|Tail]) :-
  last_word(Head, Tail).

% Split user input into question and illness
split_for_last(Question, Result) :-
  split_string(Question, " ", "?", Question_list),
  last_word(Result, Question_list).

% Rule for extracting illnesses from the "What is the difference between" question
split_difference(Question, First, Second) :-
  sub_string(Question, _, _, _, "common cold"), First = "common cold",
  sub_string(Question, _, _, _, "flu"), Second = "flu";
  sub_string(Question, _, _, _, "coronavirus"), First = "coronavirus",
  sub_string(Question, _, _, _, "flu"), Second = "flu";
  sub_string(Question, _, _, _, "common cold"), First = "common cold",
  sub_string(Question, _, _, _, "coronavirus"), Second = "coronavirus".

% Rule to answer user questions and check if they have anything else they want to do
questions :-
  read_string(user_input, '\n', '', _, Question),
  (sub_string(Question, _, _, _, "What are the common symptoms of"), split_for_last(Question, Result), common_symptoms(Result, Answer), write(Answer), nl, write("Anything else?"), nl, parse_question;
  sub_string(Question, _, _, _, "What should I do if I have symptoms of"), split_for_last(Question, Result), what_to_do(Result, Answer), write(Answer), nl, write("Anything else?"), nl, parse_question;
  sub_string(Question, _, _, _, "What are the risk factors for severe illness from"), split_for_last(Question, Result), risk_factors(Result, Answer), write(Answer), nl, write("Anything else?"), nl, parse_question;
  sub_string(Question, _, _, _, "How can I prevent the spread of"), split_for_last(Question, Result), prevent_spreading(Result, Answer), write(Answer), nl, write("Anything else?"), nl, parse_question;
  sub_string(Question, _, _, _, "What is the difference between"), split_difference(Question, First, Second), differences(First, Second, Answer), write(Answer), nl, write("Anything else?"), nl, parse_question;
  write("Sorry, I coudn't quite understand, please try again."), nl, questions).

% Start of user interaction
start :-
  write("Would you like a diagnosis or do you have a question? "), nl,
  parse_question.

% Rules to navigate to diagnosis or questions
parse_question :-
  read_string(user_input, '\n', '', _, Request),
  (Request == "diagnosis", nl, diagnosis;
   Request == "question", write("What is your question?"), nl, questions;
   Request == "no", make, start;
   Request == "goodbye", write("goodbye");
   write("Sorry, I coudn't quite understand, please try again."), nl, parse_question).
