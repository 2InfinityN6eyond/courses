package edu.skku.cs.designpattern;

import androidx.databinding.BaseObservable;
import androidx.databinding.Bindable;

public class MySimpleViewModel extends BaseObservable {
    private MySimpleModel model;

    public MySimpleViewModel() {
        model = new MySimpleModel(0);
        this.valueString = "Value: 0";
    }

    @Bindable
    private String valueString = null;

    public  String getValueString() {
        return valueString;
    }

    public void setValueString(String valueString) {
        this.valueString = valueString;
        notifyPropertyChanged(BR.valueString);
    }

    public void onAddingButtonClicked() {
        model.addOne();
        this.setValueString("Value: " + model.getValue());
    }
}
