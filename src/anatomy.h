#ifndef  ANATOMY_INC
#define  ANATOMY_INC

#include "effect.h"

#include <map>
#include <string>

// TODO: Move all this stuff to be json read, that would be uber nice.

/*-----------------------------------------------------------------------------
 *         Enum:    anatomical_function
 *  Description:    Denotes what this body part/group is needed for. Example
 *                  functions include [AF_MOVEMENT], which is used for
 *                  moving the creature (legs for a human, for example).
 *
 *                  These are abstracted standard medical concepts that may or
 *                  may not attribute to a creature. Most of these are modelled
 *                  after human medicine, but some other things will be in there
 *                  to account for things we can't do. (Sonar, uber-nose , etc)
 *-----------------------------------------------------------------------------*/
enum anatomical_function {
    // motor functions
    AF_AMBULATION = 0,                          /* orthostasis, ambulating, etc */
    // five senses
    AF_OCULAR,                                  /* sight */
    AF_OLFACTORY,                               /* smell */
    AF_AUDITORY,                                /* hearing */
    AF_GUSTATORY,                               /* taste */
    AF_TACTILE,                                 /* touch */
    // circulatory
    AF_RESPIRATORY,                             /* breathing */
    AF_NEUROVASCULAR,                           /* nervous [+ vascular] system */
    AF_CARDIOVASCULAR,                          /* heart & vascular system */
    // chassis, engine, and driver
    AF_SKELETAL,                                /* bones */
    AF_MUSCULAR,                                /* as it says */
    AF_NEUROLOGICAL,                            /* brain/nervous system */
    // non-humanoid functions
    AF_ANTENNAE,                                /* sensory perception via antennae */
    num_af
};

/* aliases for common "organ" groups, using singular version for consistency */
// motor functions
#define AF_MOVEMENT         AF_AMBULATION
// five senses
// circulatory
#define AF_LUNG             AF_RESPIRATORY
#define AF_NERVE            AF_NEUROVASCULAR
#define AF_HEART            AF_CARDIOVASCULAR
// systems
#define AF_BONE             AF_SKELETAL
#define AF_MUSCLE           AF_MUSCULAR
#define AF_NEURO            AF_NEUROLOGICAL

/*-----------------------------------------------------------------------------
 *       Struct:    anatomical_group
 *  Description:    
 *-----------------------------------------------------------------------------*/
struct anatomical_group {
    std::string                     name;       /* name of the group */
    std::string                     desc;       /* description of the group */
    anatomical_function             funcs;      /* what does this group of parts do */
    bool                            vital;      /* is this "group" vital? */
};

/*-----------------------------------------------------------------------------
 *       Struct:    anatomical_part
 *  Description:    Describes a part of the body. This could be limbs or organs
 *                  or laser beams, whatever your heart desires.
 *
 *                  The "group" in this structure is used to bunch together
 *                  similar parts, such as "organs" or "limbs" or "toes" and
 *                  the like.
 *-----------------------------------------------------------------------------*/
struct anatomical_part {
    std::string                      name;      /* name of the part */
    std::string                      desc;      /* description of the part */
    std::list<anatomical_function>  funcs;      /* what does this part do? */
    std::list<std::string>      in_groups;      /* name of the part group */
    // now comes the SUPER-FUN data!
    int hp;                                     /* how much damage can it take? */
    int health;                                 /* how healthy is this part? */

    /* [dmg_effects] is structured as:
     *  int:        key is stage of damage to this part (stages defined in json)
     *  effect:     value is list of effects that can happen at that stage
     */
    std::map<int, std::list<effect>> dmg_effects;    
};

/*
 * =====================================================================================
 *        Class:  Anatomy
 *  Description:  Describes the basic anatomy of a creature/being/mass of element
 *                (hey, I ain't biased against non-carbon lifeforms). This can initiate
 *                an arbitrary number of arbitrary organs on an arbitrary body.
 *
 *                This will handle damage to parts and organs (if they function of 
 *                course), and handle their effects (diseases, ailments, etc).
 *
 *                NOTE!!!: I would LIKE to move all bodypart junk into here to
 *                centralize it, and to prevent non-const usage of player hp[] access.
 * =====================================================================================
 */
class Anatomy
{
    public:
        /* ====================  LIFECYCLE     ======================================= */
        Anatomy ();
        Anatomy ();
        ~Anatomy ();

        /* ====================  ACCESSORS     ======================================= */
        bool get_hp() const;

        /* ====================  MUTATORS      ======================================= */
        void damage(int);

        /* ====================  OPERATORS     ======================================= */

    protected:
        /* ====================  DATA MEMBERS  ======================================= */

    private:
        /* ====================  DATA MEMBERS  ======================================= */
        std::map<std::string, anatomical_part> parts;
        std::map<std::string, anatomical_group> groups;

        std::map<std::string, int> hp;          /* hp["cur"] || hp["max"] */
        int immunity;                           /* immune system */


}; /* -----  end of class Anatomy  ----- */


#endif   /* ----- #ifndef ANATOMY_INC  ----- */
