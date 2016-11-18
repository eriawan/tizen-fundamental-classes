/*
 * TreeMenu.h
 *
 *  Created on: Feb 23, 2016
 *      Contributor:
 *        Gilang M. Hamidy (g.hamidy@samsung.com)
 *        ib.putu (ib.putu@samsung.com)
 *        Kevin Winata (k.winata@samsung.com)
 */

#ifndef TFCFW_TREEMENU_H_
#define TFCFW_TREEMENU_H_

#include <vector>
#include <string>

#include "TFC/Components/ComponentBase.h"
#include "TFC/Components/MenuItem.h"

namespace TFC {
namespace Components {

/**
 * Component that can be used to implement tree-based menu UI.
 * Internally, it uses Elm_Genlist, but it differs from GenericList component since it supports
 * item hierarchy (parent items with its sub menu items), and built-in item expand/contract mechanism.
 */
class LIBAPI TreeMenu:
	public ComponentBase,
	EventEmitterClass<TreeMenu>,
	PropertyClass<TreeMenu>
{
	using EventEmitterClass<TreeMenu>::Event;
	using PropertyClass<TreeMenu>::Property;
private:
	Evas_Object* genlist;
	Elm_Genlist_Item_Class* itemClass;
	Elm_Genlist_Item_Class* submenuItemClass;
	Elm_Object_Item* currentlySelected;
	std::vector<MenuItem*> rootMenu;
	std::string iconEdjeFile;

	bool isScrolled;
	bool autoExpand;

	void GenerateRootMenu();
	void GenerateSubMenu(MenuItem* subMenu);
	const std::vector<MenuItem*>& GetMenuItems() const;

	bool GetAutoExpanded() const;
	void SetAutoExpanded(const bool& val);

	std::string const& GetIconEdjeFile() const;
	void SetIconEdjeFile(std::string const& val);

	typedef EFL::EvasSmartEventObjectBase<Elm_Object_Item> GenlistEvent;

	void MenuScrollInternal(Evas_Object* objSource, Elm_Object_Item* eventData);
	void MenuPressedInternal(Evas_Object* objSource, Elm_Object_Item* eventData);
	void MenuReleasedInternal(Evas_Object* objSource, Elm_Object_Item* eventData);
	void MenuSelectedInternal(Evas_Object* objSource, Elm_Object_Item* eventData);
	void MenuUnselectedInternal(Evas_Object* objSource, Elm_Object_Item* eventData);
	void MenuExpanded(Evas_Object* objSource, Elm_Object_Item* eventData);
	void MenuContracted(Evas_Object* objSource, Elm_Object_Item* eventData);
	void AppendMenuToGenlist(MenuItem* menu);

	GenlistEvent eventMenuScrollInternal;
	GenlistEvent eventMenuPressedInternal;
	GenlistEvent eventMenuReleasedInternal;
	GenlistEvent eventMenuSelectedInternal;
	GenlistEvent eventMenuUnselectedInternal;
	GenlistEvent eventMenuExpanded;
	GenlistEvent eventMenuContracted;

protected:
	/**
	 * Method overriden from ComponentBase, creates the UI elements of the component.
	 *
	 * @param root The root/parent given for this component.
	 *
	 * @return An Elm_Genlist widget.
	 */
	virtual LIBAPI Evas_Object* CreateComponent(Evas_Object* root);

public:
	/**
	 * Constructor for TreeMenu.
	 */
	TreeMenu();

	/**
	 * Method to add MenuItem to the tree menu.
	 *
	 * @param menu MenuItem that will be added.
	 */
	void AddMenu(MenuItem* menu);

	/**
	 * Method to add MenuItem at a specific position to the tree menu.
	 *
	 * @param index Index that indicates where the item will be placed.
	 * @param menu MenuItem that will be added.
	 */
	void AddMenuAt(int index, MenuItem* menu);

	/**
	 * Method to remove a particular MenuItem from the tree menu.
	 *
	 * @param menu MenuItem that will be removed.
	 */
	void RemoveMenu(MenuItem* menu);

	/**
	 * Method to bulk-add MenuItems to the tree menu.
	 *
	 * @param listOfMenus Vector that contains MenuItems that will be added.
	 */
	void AddMenu(const std::vector<MenuItem*>& listOfMenus);

	/**
	 * Destructor of TreeMenu.
	 */
	virtual ~TreeMenu();

	/**
	 * Boolean that will change clicking behavior of the tree menu.
	 * If it is true, then when an item will be selected/unselected on a single click and stays on that status.
	 * If it is false, then an item will only be selected only when user holds on the item and will be unselected on release.
	 */
	bool isClickPersist;

	/**
	 * Method to reset currently selected item to nullptr.
	 * Note that it will not change the UI state.
	 * It can be used to manipulate the tree menu to call OnMenuSelected again on item click even though it's still selected.
	 */
	void ResetCurrentlySelectedItem();


	// TODO Reimplement with correct Property declaration
	/**
	 * Property that can be filled to set the expand/contract icon edje file.
	 * The return/parameter type is string.
	 */
	Property<std::string const&>::GetSet<
			&TreeMenu::GetIconEdjeFile,
			&TreeMenu::SetIconEdjeFile> IconEdjeFile;

	/**
	 * Property that enables getting the menu items vector.
	 * The return type is vector reference.
	 */
	Property<std::vector<MenuItem*> const&>::Get<&TreeMenu::GetMenuItems> MenuItems;

	/**
	 * Property that enables getting & setting auto expanding feature of the tree menu.
	 * The return/parameter type is bool.
	 */
	Property<bool>::GetSet<&TreeMenu::GetAutoExpanded, &TreeMenu::SetAutoExpanded> AutoExpanded;

	/**
	 * Event that will be triggered when a menu item is selected.
	 */
	Event<MenuItem*> OnMenuSelected;
};

}
}



#endif /* TREEMENU_H_ */