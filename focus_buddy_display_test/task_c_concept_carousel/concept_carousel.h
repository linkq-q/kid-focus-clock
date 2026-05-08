#pragma once
typedef enum { CONCEPT_AI_REPORT = 0, CONCEPT_BADGE_WALL = 1, CONCEPT_COUNT = 2 } ConceptPage;
void carousel_setup();
void carousel_loop();
void carousel_goto(ConceptPage page);
ConceptPage carousel_current();
