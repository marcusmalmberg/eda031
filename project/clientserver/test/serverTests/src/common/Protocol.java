package common;

/** Protocol defines the basic protocol codes.
 */
public class Protocol {
    public static final int 
    COM_LIST_NG = 1,
	COM_CREATE_NG = 2,
	COM_DELETE_NG = 3,
	COM_LIST_ART = 4,
	COM_CREATE_ART = 5,
	COM_DELETE_ART = 6,
	COM_GET_ART = 7,
	COM_END = 8,

	ANS_LIST_NG = 20,
	ANS_CREATE_NG = 21,
	ANS_DELETE_NG = 22,
	ANS_LIST_ART = 23,
	ANS_CREATE_ART = 24,
	ANS_DELETE_ART = 25,
	ANS_GET_ART = 26,
	ANS_END = 27,
	ANS_ACK = 28,
	ANS_NAK = 29,

	PAR_STRING = 40,
	PAR_NUM = 41,

	ERR_NG_ALREADY_EXISTS = 50,
	ERR_NG_DOES_NOT_EXIST = 51,
	ERR_ART_DOES_NOT_EXIST = 52,
	ERR_UNSPECIFIED = 53;

    /** Convert a code value to the corresponding string.
	@param code The code value
	@return The corresponding string ("" if the code is undefined)
    */
    public static String codeString(int code) {
    	switch (code) {
    	case COM_LIST_NG:    return "COM_LIST_NG";
    	case COM_CREATE_NG:  return "COM_CREATE_NG";
    	case COM_DELETE_NG:  return "COM_DELETE_NG";
    	case COM_LIST_ART:   return "COM_LIST_ART";
    	case COM_CREATE_ART: return "COM_CREATE_ART";
    	case COM_DELETE_ART: return "COM_DELETE_ART";
    	case COM_GET_ART:    return "COM_GET_ART";
    	case COM_END:        return "COM_END";

    	case ANS_LIST_NG:    return "ANS_LIST_NG";
    	case ANS_CREATE_NG:  return "ANS_CREATE_NG";
    	case ANS_DELETE_NG:  return "ANS_DELETE_NG";
    	case ANS_LIST_ART:   return "ANS_LIST_ART";
    	case ANS_CREATE_ART: return "ANS_CREATE_ART";
    	case ANS_DELETE_ART: return "ANS_DELETE_ART";
    	case ANS_GET_ART:    return "ANS_GET_ART";
    	case ANS_END:        return "ANS_END";
    	case ANS_ACK:        return "ANS_ACK";
    	case ANS_NAK:        return "ANS_NAK";

    	case PAR_STRING:     return "PAR_STRING";
    	case PAR_NUM:        return "PAR_NUM";

    	case ERR_NG_ALREADY_EXISTS:  return "ERR_NG_ALREADY_EXISTS";
    	case ERR_NG_DOES_NOT_EXIST:  return "ERR_NG_DOES_NOT_EXIST";
    	case ERR_ART_DOES_NOT_EXIST: return "ERR_ART_DOES_NOT_EXIST";
    	case ERR_UNSPECIFIED:        return "ERR_UNSPECIFIED";

    	default: return "";
    	}
    }
}
	
