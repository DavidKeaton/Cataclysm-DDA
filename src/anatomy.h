#ifndef  ANATOMY_INC
#define  ANATOMY_INC

#include "effect.h"

#include <map>
#include <string>


/*-----------------------------------------------------------------------------
 *         Enum:    anatomical_function
 *  Description:    Denotes what this body part/group is needed for. Example
 *                  functions include [AF_MOVEMENT], which is used for
 *                  moving the creature (legs for a human, for example).
 *-----------------------------------------------------------------------------*/
enum anatomical_function {
    AF_MOVEMENT = 0,
    AF_RESPIRATORY,
    AF_CARDIOVASCULAR,
    AF_SKELETAL,
    AF_MUSCULAR,
    num_af
};

// aliases for common "organ" groups
// NOTE: leaving these as singular to make a common theme
#define AF_LUNG     AF_RESPIRATORY
#define AF_HEART    AF_CARDIOVASCULAR
#define AF_BONE     AF_SKELETAL
#define AF_MUSCLE   AF_MUSCULAR

/*-----------------------------------------------------------------------------
 *       Struct:    anatomical_group
 *  Description:    
 *-----------------------------------------------------------------------------*/
struct anatomical_group {
    std::string                 name;           /* name of the group */
    std::string                 desc;           /* description of the group */
    anatomical_function         funcs;          /* what does this group of parts do */
    bool                        vital;          /* is this "group" vital? */
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
    std::string                 name;           /* name of the part */
    std::string                 desc;           /* description of the part */
    anatomical_function         funcs;          /* what does this part do? */
    std::list<std::string>      in_groups;      /* name of the part group */
    // now comes the SUPER-FUN data!
    int health;                                 /* how much damage can it take? */
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
        Anatomy ();                             /* constructor */

        ~Anatomy ();                            /* deconstructor */

        /* ====================  ACCESSORS     ======================================= */

        /* ====================  MUTATORS      ======================================= */

        /* ====================  OPERATORS     ======================================= */

    protected:
        /* ====================  DATA MEMBERS  ======================================= */

    private:
        /* ====================  DATA MEMBERS  ======================================= */
        std::map<std::string, anatomical_part> parts;
        std::map<std::string, anatomical_group> groups;


}; /* -----  end of class Anatomy  ----- */


#endif   /* ----- #ifndef ANATOMY_INC  ----- */
