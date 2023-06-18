#include "../include/typingtest.h"
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void test_load_paragraph() {
    TypingTest typing_test;
    memset(&typing_test, 0, sizeof(TypingTest));
    char current_path[PATH_MAX];
    if (getcwd(current_path, sizeof(current_path)) == NULL) {
        fprintf(stderr, "Failed to get the current working directory.\n");
        return;
    }
    char absolute_path[PATH_MAX];
    snprintf(absolute_path, sizeof(absolute_path), "%s/data/default_paragraph.txt", current_path);
    char* expteced = "topdress reorientate please make overstay toddle clot heat siphon optimize stoop carry retrofit oxidise hood pump dart intrude scramble caulk grizzle rosin seed cry accrue come assign down reflect contemplate demythologize want grimace segregate lift baronetize act exfoliate muff rekindle exemplify redirect ostracize anticipate absolve walk whizz angle excavate tintinnabulate weather pomade leak redefine seethe poison splay endeavor range rusticate desacralize interview brooch break bread shave ride get stick trench key pass dust harp drag nitrate croquet hint orient tempt lose quell unbalance range poise receive deepen learn imitate task analyze rest displease crash masquerade trench separate whang overawe govern anguish cork sermonize plop impeach federalize post automatize industrialize disable conquer uncloak amuse sign conclude welcome mushroom refute harmonize regenerate defuse duck throne warble facilitate check caseate overlie bestir function preclude wilt fire rectify legislate readmit have pouch stumble ream demand cramp wheedle kill conclude cartwheel brush logroll collapse define chute construct scavenge echo chug maneuver fly wire float close hawk inflate drag communicate wrangle govern disarrange underplay avow vinify populate devour wallow pump chariot referee spell dine dump mythicize rag reverberate assonate proportion run revoke rein dissipate complete rape silverplate cement transfuse mushroom ventilate dangle say face bedizen shuffle wallow sit unblock squall outnumber quarter twirl prizefight duplicate excommunicate loom mushroom explode reach swaddle prevail coconspire interpose shipwreck leverage develop dream church want gurgle right decompress bite desert decaffeinate whish cut blink stick count exist radiate disengage recover touch buck capitalize lengthen mobilize adore think syllabize construct park assure ordain shoot bachelor set effect piggyback rack intensify pigment waste submit offer backstitch block deduce twang carry wink reecho volunteer kitten port involve circumstantiate ride scan flocculate shift top broom topdress recharge copper predominate answer depress overjoy char dignify pick lap careen diverge puncture drop compete silhouette sport desalinate scour outwit freeze fodder coarsen abuse imprison call welt call dial trench denaturalize flinch intern implicate avianize chug attenuate work whittle dominate grade surprise milk partake retreat settle circulate abacinate enucleate restore immortalize garrison pickle syllabify ghost unbutton follow submarine translate prowl unblock predict scrub chitter Frenchify pluck fan clinker frock";
    load_paragraph(&typing_test, absolute_path);
    int compared = strcmp(typing_test.paragraphs[0], expteced);
    assert(typing_test.num_paragraphs == 1);
    assert(compared == 0);
}

int main() {
    test_load_paragraph();
    printf("All tests passed.\n");
    return 0;
}

