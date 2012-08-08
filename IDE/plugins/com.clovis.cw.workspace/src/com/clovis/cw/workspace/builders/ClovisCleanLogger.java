/*******************************************************************************
 * ModuleName  : com
 * $File: //depot/dev/main/Andromeda/IDE/plugins/com.clovis.cw.workspace/src/com/clovis/cw/workspace/builders/ClovisBuilderLogger.java $
 * $Author: bkpavan $
 * $Date: 2007/01/03 $
 *******************************************************************************/

/*******************************************************************************
 * Description :
 *******************************************************************************/

package com.clovis.cw.workspace.builders;



/**
 * @author Pushparaj
 * Logger for the Clean.
 */
public class ClovisCleanLogger extends ClovisActionLogger
{
    /**
	 * Constructor.
     * Sets console title as well as success and fail messages.
	 */
    public ClovisCleanLogger()
    {
        super("Clean Project");
    }
}