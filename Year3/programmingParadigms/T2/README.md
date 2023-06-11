# Task 2 (Prolog): Is it cold, flu or COVID-19? (Expert System)


> "In artificial intelligence, an expert system is a computer system emulating the decision-making ability of a human expert.
> Expert systems are designed to solve complex problems by reasoning through bodies of knowledge, represented mainly as if–then rules rather than through conventional procedural code.
> The first expert systems were created in the 1970s and then proliferated in the 1980s. Expert systems were among the first truly successful forms of artificial intelligence (AI) software.
>
> An expert system is divided into two subsystems: the **inference engine** and the **knowledge base**. The _knowledge base_ represents facts and rules. The _inference engine_ applies the rules to the known facts to deduce new facts. Inference engines can also include explanation and debugging abilities."
> [Wikipedia, 2023]

Design and implement an Expert System (ES) in Prolog that can **diagnose** and **provide information** on the symptoms of cold, common flu, and COVID-19.
Additionally, your ES should be able to provide information on how to **manage** the symptoms and **prevent the spread** of the condition to others.

Start by reading the chapter in the file "*D. Crookes - An application in Medicine.pdf*".

1) Create your *knowledge base* by coding the official NHS symptoms **facts** available from:

  - <https://www.nhs.uk/conditions/common-cold/>
  - <https://www.nhs.uk/conditions/flu/>
  - <https://www.nhs.uk/conditions/coronavirus-covid-19/symptoms/main-symptoms/>

    Add other facts and **rules** from *reliable* sources, and ensure you give citations/links to the sources.

    Alongside diagnosis, the system should be able to address the following questions about a given condition "C":

    - What are the common symptoms of C?
    - What should I do if I have symptoms of C?
    - What are the risk factors for severe illness from C?
    - How can I prevent the spread of C?
    - What is the difference between C1 and C2?
