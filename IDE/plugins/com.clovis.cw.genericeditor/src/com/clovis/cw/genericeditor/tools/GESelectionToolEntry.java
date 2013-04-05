/*******************************************************************************
 * ModuleName  : com
 * $File: //depot/dev/main/Andromeda/IDE/plugins/com.clovis.cw.genericeditor/src/com/clovis/cw/genericeditor/tools/GESelectionToolEntry.java $
 * $Author: bkpavan $
 * $Date: 2007/01/03 $
 *******************************************************************************/

/*******************************************************************************
 * Description :
 *******************************************************************************/

package com.clovis.cw.genericeditor.tools;

import org.eclipse.gef.Tool;
import org.eclipse.gef.palette.SelectionToolEntry;
import org.eclipse.jface.util.Assert;

import com.clovis.cw.genericeditor.GenericEditor;

/**
 * @author pushparaj
 *
 */
public class GESelectionToolEntry extends SelectionToolEntry {
	
	private Class _toolClass;
	private GenericEditor _editor;
	
	/**
	 * Creates a new SelectionToolEntry.
	 */
	public GESelectionToolEntry(GenericEditor editor) {
		this(null, editor);
	}

	/**
	 * Constructor for SelectionToolEntry.
	 * @param label the label
	 */
	public GESelectionToolEntry(String label, GenericEditor editor) {
		this(label, null, editor);
	}
	/**
	 * Constructor for GESelectionToolEntry.
	 * @param label the label
	 * @param shortDesc the description
	 */
	public GESelectionToolEntry(String label, String shortDesc, GenericEditor editor) {
		super(label, shortDesc);
		_editor = editor;
		setToolClass(GESelectionTool.class);
	}
	/**
	 * Creates the tool of the type specified by {@link #setToolClass(Class)} for this 
	 * ToolEntry.  The tool is also configured with the properties set in 
	 * {@link #setToolProperty(Object, Object)}.  Sub-classes overriding this method should
	 * ensure that their tools are also configured with those properties.
	 * @return the tool for this entry
	 */
	public Tool createTool() {
		if (_toolClass == null)
			return null;
		GESelectionTool tool;
		try {
			tool = (GESelectionTool)_toolClass.newInstance();
			tool.setEditor(_editor);
		} catch (IllegalAccessException iae) {
			return null;
		} catch (InstantiationException ie) {
			return null;
		}
		tool.setProperties(getToolProperties());
		return tool;
	}
	/**
	 * Sets the type of tool to be created.  This provides clients with a method of specifying
	 * a different type of tool to be created without having to sub-class.  The provided class
	 * should have a default constructor for this to work successfully.
	 * @param toolClass the type of tool to be created by this entry
	 * @since 3.1
	 */
	public void setToolClass(Class toolClass) {
		if (toolClass != null)
			Assert.isTrue(Tool.class.isAssignableFrom(toolClass));
		this._toolClass = toolClass;
	}

}