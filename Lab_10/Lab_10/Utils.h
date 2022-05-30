#pragma once
#include "Locatar.h"

//Utility function used as comparator for sorting functions. It compares the numeProprietar fields of the given objects so they are in an increasing order.
bool CompareLocatarsNumeCresc(const Locatar& a, const Locatar& b);

//Utility function used as comparator for sorting functions. It compares the type + surface fields of the given objects so they are in an increasing order.
bool CompareLocatarsTypePlusSuprafataCresc(const Locatar& a, const Locatar& b);

//Utility function used as comparator for sorting functions. It compares the surface fields of the given objects so they are in an increasing order.
bool CompareLocatarsSuprafataCresc(const Locatar& a, const Locatar& b) noexcept;

//Utility function used as comparator for sorting functions. It compares the numeProprietar fields of the given objects so they are in an decreasing order.
bool CompareLocatarsNumeDescresc(const Locatar& a, const Locatar& b);

//Utility function used as comparator for sorting functions. It compares the type + surface fields of the given objects so they are in an decreasing order.
bool CompareLocatarsTypePlusSuprafataDescresc(const Locatar& a, const Locatar& b);

//Utility function used as comparator for sorting functions. It compares the surface fields of the given objects so they are in an decreasing order.
bool CompareLocatarsSuprafataDescresc(const Locatar& a, const Locatar& b) noexcept;