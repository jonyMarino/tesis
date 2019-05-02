package org.eclipse.acceleo.module.oopc.services;

import java.util.List;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

import org.eclipse.emf.common.util.EList;
import org.eclipse.uml2.uml.Class;


public class UML2OOPCServices {
	 
	
	public Set<List<Class>> getPathsJAVA(Class fromClass, Class toClass) {
		    
		Set<List<Class>> result = new HashSet<List<Class>>();
		 
		if (fromClass == toClass){
			//ArrayList<Class> justTheClass = new ArrayList<Class>();
			//justTheClass.add(toClass);
			//result.add(justTheClass); 
			return result;
		}
		 
		EList<Class> superClasses = fromClass.getSuperClasses();
		 
		if(superClasses.isEmpty()){
			//ArrayList<Class> justTheClass = new ArrayList<Class>();
			//justTheClass.add(fromClass);
			//result.add(justTheClass); 
			return result;
		}
		
		for (Class superClass : superClasses) {
			Set<List<Class>> subPath = getPathsJAVA(superClass, toClass);
			if (subPath.isEmpty() && superClass==toClass){
				ArrayList<Class> justTheClass = new ArrayList<Class>();
				justTheClass.add(toClass);
				result.add(justTheClass);
			}
			else{
				for(List<Class> path : subPath){
					path.add(0, superClass);
					result.add(path);
				}	
			}
		}
		 
		 
		 
		return result;
	 }
	 
	 
		 
}
